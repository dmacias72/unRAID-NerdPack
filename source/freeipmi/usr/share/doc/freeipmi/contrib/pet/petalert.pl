#!/usr/bin/perl -w

# This is snmptrapd handler script to alert Platform Event Traps (PET).
# I wrote it because traptoemail distributed with net-snmp-5.3.2.2 is 
# incapable of handling multi-line hexstrings and restricted to email alert. 
#
# This script operates in two modes, traphandle or embperl.  When in 
# traphandle mode, it concatenates the quoted hex string into one long line, 
# then builds structures to resemble embperl mode. Both modes then invokes 
# helper decoder, ipmi-pet(8) from FreeIPMI, parses the output and alerts
# in given way like email, nagios external command, etc. See README for 
# a simple tutorial.
#
# This script is tested on Dell PowerEdge 1950 and PowerEdge R610 servers. 
# Feel free to adjust to meet your need. It's BSD-licensed.
#
# ChangeLog
#
# * Fri 16 Dec 2011 kaiwang.chen@gmail.com
# - Re-add nsca support.
# - Protect against hex string for traphandle missing ending whitespace.
#
# * Wed 14 Dec 2011 kaiwang.chen@gmail.com
# - Add performance logging support with 'perf' token
#
# * Mon 12 Dec 2011 kaiwang.chen@gmail.com
# - Remove nsca support because snmptrapd is meant to run on the Nagios host
# - Fix nagios external command file support
# - Map FreeIPMI Nominal state to Nagios OK
# - Fix Net::SMTP typos and options handling
# - Remove USAGE section, please refer to README
#
# * Sun 11 Dec 2011 kaiwang.chen@gmail.com
# - Add -W to pass workaround flags to ipmi-pet
#
# * Wed 7  Dec 2011 kaiwang.chen@gmail.com
# - Add --ack support
# - capture exit code of helper
#
# * Mon 14 Nov 2011 kaiwang.chen@gmail.com
# - complete rewritten, supports embperl mode and additional alert methods
#
# * Sat 12 Nov 2011 kaiwang.chen@gmail.com
# - support sdr cache file mapping with -c option
# - add debug log
# - in case of no PTR, fallback to ip
#
# * Sun 06 Nov 2011 kaiwang.chen@gmail.com
# - Inital version

package IpmiPET::Perf;
use Time::HiRes qw(tv_interval gettimeofday);
sub new {
  bless {
    _elapsed => 0,
  }, __PACKAGE__;
}
sub start { shift->{_start} = [gettimeofday] }
sub stop {
  my ($obj,$name) = @_;
  my $t1 = [gettimeofday];
  my $t = tv_interval($obj->{_start}, $t1);
  $obj->{_elapsed} += $t;
  if ($name) { 
    $obj->{_laps}{$name} = $t;
  }
  return $t;
}
sub reset {
  my ($obj) = @_;
  $obj->{_elapsed} = 0;
  if ($obj->{_start}) { delete $obj->{_start} }
  if ($obj->{_laps}) { delete $obj->{_laps} }
}
sub elapsed { shift->{_elapsed} }
sub laps { shift->{_laps} }
1;


package IpmiPET;

use strict;
use Getopt::Long;

# mapping IPMI nodes to preinitialized sdr caches
my %cache_mapping=();

# options
my %opts = ();

# options and args pass to specific alert mechanisms
my %alert_opts = (); # when use builtin features to alert
my $alert_prog = ""; # when use external program to alert

# logger
my $log_filename = "/var/log/petalert.log";
my %logger_token = ('warn' => 1); # always warn

# performance ticker
my $perf;


sub usage {
    print <<"EOF";
USAGE

$0 [OPTIONS] -- [ALERT_SPECIFIC_OPTIONS] ALERT_SPECIFIC_ARGS

  OPTIONS
    -m
    --mode  {traphandle|embperl} 
                Specify mode of execution. Required.
    --ack
                Acknowledge the trap before alert.
    -W
    --workaround
                Sets workaround flags for ipmi-pet to acknowledge the trap.
    -o
    --trapoid  OID
                Sets trapoid in embperl mode, or defaults to "all".
    -c
    --sdrcache  sdr_cache_config 
                Specify the sdr cache configuration file.
    -f
    --log  log_file
                Specify logging file
    -n
    --alert  {mail|nagios|nsca|noop|MODULE}
                Specify alert method. Defaults to "noop".

  ALERT SPECIFIC OPTIONS AND ARGS
  email
    --prog  mailer
                Sets mailer. If not specified, falls back to Net::SMTP.
    mailer_options_and_args

    --server smtp_server
                Sets the smtpserver for Net::SMTP to send the mail through.
                Defaults to "localhost".
    --from from_address
                Sets the email for Net:SNMP to be used on the From: line.
                Defaults to "root".
    to_addresses
                Sets where you want Net::SMTP to send the email to. Required.
    
  nagios
    --host  {fqdn|short}
                Sets host in nagios external commands. Defaults to short (first component).
    --service
                Sets service in nagios external commands. Defaults to PET.
    command_file
                Sets Nagios external command file, a named pipe (FIFO).
                Required.
  nsca
    --prog  send_nsca
                Sets path to send_nsca binary, required.
    --host  {fqdn|short}
                Sets host for the passive check. Defaults to short (first component).
    --service
                Sets service for the passive check. Defaults to PET.
    -- send_nsca_options_and_args
                Pass options and args through to send_nsca binary.

  noop          Yes, it is a no-op.

  MODULE <not implemented>
    --prog plugin
                Path to plugin script, which must provides..
    plugin_options_and_args
                Additional arguments passed to plugin as \@ARGV.
EOF

  exit;
}

sub logger {
  my ($token, $msg, $variable) = @_;
  $token ||= "";

  if (open my $fh, ">>", $log_filename) {
    if ($logger_token{":all"} || $logger_token{$token}) {
      if ($variable) {
        use Data::Dumper;
        my $t = $Data::Dumper::Terse;
        $Data::Dumper::Terse = 1;
        print $fh "[".localtime()."] $token $msg " . Dumper($variable);
        $Data::Dumper::Terse = $t;
      }
      else {
        print $fh "[".localtime()."] $token $msg\n";
      }
    }
    close $fh;
  }
}

# extract ip from value like "UDP: [172.23.252.107]:32768"
sub extract_ip {
  my ($ip) = ($_[0] =~ /\[([\d.]+)\]:/);
  return $ip || "0.0.0.0";
}

# decode specified event hexstring into hash like
#   'Time' => '13:16:24',
#   'Event' => 'General Chassis Intrusion ; Intrusion while system On',
#   'System_ID' => '256',
#   'State' => 'Critical',
#   'GUID' => '44454c4c-5000-1059-8043-b2c04f333358',
#   'Date' => 'Oct-15-2011',
#   'Manufacturer_ID' => 'Dell Inc.',
#   'Name' => 'Sensor #115',
#   'Severity' => 'N/A',
#   'Event_Direction' => 'Assertion Event',
#   'Type' => 'Physical_Security'
#
sub decode_pet {
  my ($specific, $event_hexstring, $sdrcache) = @_;

  my $ipmi_pet = "/usr/sbin/ipmi-pet";
  my @o = qw(-v -v --output-event-severity --output-event-state --interpret-oem-data --comma-separated-output);
  if ($sdrcache) { push @o, "--sdr-cache-file", $sdrcache }
  push @o, $specific;
  $event_hexstring =~ tr/0-9a-fA-F/ /cs; # sanity check
  $event_hexstring =~ s/^\s+//; # in case of (split/\s+/)[0] being ""
  push @o, split /\s+/, $event_hexstring;

  my @x = ();
  logger("decode", "command line ", [$ipmi_pet, \@o]);
  if (open my $fh, "-|", $ipmi_pet, @o) {
    @x = <$fh>;
    close $fh;
    if ($? >> 8) {
      logger("warn", "decode failure with CHILD_ERROR: $?");
      return;
    }
  }
  else {
    logger("warn", "decoder failure: $!");
    return;
  }
  chomp(@x);

  logger("decode", "output ", \@x);
  my @headers = split /,/, $x[0];
  my @values = split /,/, $x[1];  # TODO support doubly quoted value
  if (@headers != @values) {
    logger("warn", "Spot malicious comma separated value", \@x);
  }
  my %event = ();
  for my $i (0..$#headers) {
    my $h = $headers[$i];
    $h =~ s/ /_/g;
    $event{$h} = $values[$i];
  }
  logger("decode", "event ", \%event);
  return \%event;
}

sub ack_pet {
  my ($specific, $event_hexstring, $host, $workaround) = @_;

  my $ipmi_pet = "/usr/sbin/ipmi-pet";
  my @o = qw(--pet-acknowledge);
  if ($workaround) {
    push @o, "-W", $workaround;
  }
  push @o, "-h", $host;
  push @o, $specific;
  $event_hexstring =~ tr/0-9a-fA-F/ /cs; # sanity check
  $event_hexstring =~ s/^\s+//; # in case of (split/\s+/)[0] being ""
  push @o, split /\s+/, $event_hexstring;

  my @x = ();
  logger("ack", "command line ", [$ipmi_pet, \@o]);
  if (open my $fh, "-|", $ipmi_pet, @o) {
    @x = <$fh>;
    close $fh;
    if ($? >> 8) {
      logger("warn", "ackhelper failure with CHILD_ERROR: $?");
    }
  }
  else {
    logger("warn", "ackhelper failure: $!");
  }
}

# ipmi-pet localtime to calendar time
sub pettime {
  my ($event) = @_;
  require POSIX;
  my ($hour,$min,$sec) = split /:/, $event->{Time};
  my ($mon,$mday,$year) = split /-/, $event->{Date};
  $year -= 1900;
  my %m = (
    Jan => 0, Feb =>  1, Mar =>  2, Apr => 3, May =>  4, Jun =>  5,
    Jul => 6, Aug =>  7, Sep =>  8, Oct => 9, Nov => 10, Dec => 11,
  );
  if (exists $m{$mon}) { $mon = $m{$mon} }
  else {
    logger("warn", "pettime month $mon will map to 0, please check ipmi-pet");
    $mon = 0;
  }
  return POSIX::mktime($sec, $min, $hour, $mday, $mon, $year);
}

# convert event to nagios plugin output
# See http://nagios.sourceforge.net/docs/3_0/pluginapi.html
sub nagios_check {
  my ($event) = @_;
  my ($code, $state);

  $state = uc($event->{State});
  if    ($state eq "WARNING")  {$code = 1}
  elsif ($state eq "CRITICAL") {$code = 2}
  elsif ($state eq "OK")       {$code = 0}
  elsif ($state eq "NOMINAL")  {$code = 0; $state = "OK"}
  else                         {$code = 3; $state = "UNKNOWN"}

  my $plugin_output = join(" ", $state, "-", map { defined $_ ? $_ : "" } @{%{$event}}{qw(Name Type Event_Direction Event)});
  $plugin_output =~ tr/\n\t;|/@:/;

  return ($code, $plugin_output);
}
sub nagios_host {
  my ($pdu_info, $opt) = @_;
  my $h = $pdu_info->{hostname};
  if ($opt eq 'short') {
    ($h) = ($pdu_info->{hostname} =~ m/([^.]+)/);
  }
  return $h;
}

# assemble SMTP DATA, http://cr.yp.to/smtp/mail.html
# TODO return encoded data
sub mail_data {
  my ($from, $to, $pdu_info, $uptime, $event) = @_;

  local $" = ", "; # " balance
  my $data = <<"DATA";
To: @{$to}
From: $from
Subject: PET from $pdu_info->{hostname}: $event->{State} - $event->{Event}

Host: $pdu_info->{hostname} ($pdu_info->{receivedfrom}) uptime $uptime
DATA

  for my $k (qw(Date Time Name Type Event Event_Direction State Severity GUID Manufacturer_ID System_ID)) {
    $data .= "$k: $event->{$k}\n";
  }

  return $data;
}

# embperl NetSNMP::TrapReceiver trap receiver
sub my_receiver {
  my ($pdu_info, $varbindings) = @_;

  #use Data::Dumper;print Dumper($pdu_info); print Dumper($varbindings);
  logger("embperl", "original input is ", \@_);

  # inject hostname
  unless (exists $pdu_info->{hostname}) {
    use Socket;
    my $ip = extract_ip($pdu_info->{receivedfrom});
    $perf->start;
    $pdu_info->{hostname} = gethostbyaddr(inet_aton($ip), AF_INET) || $ip;
    $perf->stop("resolv");
  }

  # do cleanup before processing; values are untouched if -OQ, see snmpcmd(1)
  for (@$varbindings) {
    $_->[1] =~ s/^OID: //;
    $_->[1] =~ s/^IpAddress: //;
    $_->[1] =~ s/^STRING: //;
    $_->[1] =~ s/^Hex-STRING: //;
    if ($_->[1] =~ s/^Timeticks: //) {
      $_->[1] =~ s/^\(\d+\) //;
      $_->[1] =~ s/ days, /:/;
    }
  }
  logger("embperl", "input after cleanup is ", \@_);

  process($pdu_info, $varbindings);
  my $laps = $perf->laps;
  logger("perf", join(", ", map { $_ . "=" . $laps->{$_} } keys %{$laps}));
  $perf->reset;
}

# you got it..
sub process {
  my ($pdu_info, $varbindings) = @_;
  my ($event_oid, $specific, $uptime, $event);

  # locate the PET event hex string, and extract specific trap number
  for my $v (@{$varbindings}) {
    if ($v->[0] =~ /^\Q.1.3.6.1.6.3.1.1.4.3.0\E$/) {
      $event_oid = $v->[1];
    }
    if ($v->[0]=~ /^\Q.1.3.6.1.6.3.1.1.4.1.0\E$/) {
      ($specific)=($v->[1]=~/(\d+)$/);
    }
    if ($v->[0] =~ /^\Q.1.3.6.1.2.1.1.3.0\E$/) {
      $uptime = $v->[1];
    }
  }
  $event_oid .= ".1";

  $uptime ||= "00:00:00:00.00";
  if (my ($d,$H,$M,$S,$x) = ($uptime =~ /(\d+):(\d+):(\d+):(\d+)\.(\d+)/)) {
    if ($d > 0)    { $uptime = "${d}d${H}h" }
    elsif ($H > 0) { $uptime = "${H}h${M}m" }
    elsif ($M > 0) { $uptime = "${M}m${S}s" }
    else           { $uptime = "${S}.${x}s" }
  }
  
  # convert event string to human readable form
  for my $v (@{$varbindings}) {
    if ($v->[0] =~ /^\Q$event_oid\E$/) {
      my $ip = extract_ip($pdu_info->{receivedfrom});
      if ($opts{ack}) {
        $perf->start;
        ack_pet($specific, $v->[1], $ip, $opts{workaround});
        $perf->stop("ack");
      }

      my $sdrcache = resolve_sdrcache($ip);
  
      # decode octet hex string
      $event = decode_pet($specific, $v->[1], $sdrcache);
    }
  }

  # invalid events cease here
  return unless $event;

  alert($pdu_info, $uptime, $event);
  return;
}

# build NetSNMP::TrapReceiver style structures from standard input
#  See NOTIFICATION PROCESSING snmptrapd.conf(5)
sub get_from_stdin {
  my ($stdin) = @_;
  my $hostname = shift @{$stdin};
  my $ipaddress = shift @{$stdin};

  chomp($hostname);
  chomp($ipaddress);

  # in case of no PTR records available for the IPMI node
  if($hostname eq "<UNKNOWN>" && (my $ip = extract_ip($ipaddress))) {
    $hostname = $ip;
  }

  # some defaults, blindly.. to resemble those by NetSNMP::TrapReceiver
  my %pdu_info = (
    notificationtype   =>  "TRAP",
    hostname           =>  $hostname,
    receivedfrom       =>  $ipaddress,
    version            =>  0,
    errorstatus        =>  0,
    messageid          =>  0,
    transactionid      =>  1,
    errorindex         =>  0,
    requestid          =>  0,
  );
  
  my @varbindings= ();
  my ($oid,$value);
  my $more = 0;
  my $line = "";
  for (@{$stdin}) {
      if ($more == 0 && $line) {
          $line =~ s/\n\Z//s;
          ($oid, $value) = ($line =~ /([^\s]+)\s+(.*)/s);
          $line = "";
          push @varbindings, [$oid, $value, "="];
      }
  
      # recognize doubly quoted context
      my $count = 0;
      my $x = -1;
      $x=index($_, q{"});
      while ($x >= 0) {
         unless ($x > 0 && substr($_, $x-1, 1) eq "\\") {
             $count++;
         }
         $x += 1;
         $x=index($_, q{"}, $x);
      }
      if ($count % 2 == 1) {
          $more = $more == 1 ? 0 : 1;
      }
  
      $line .= "$_\n";
  }
  if ($line) {
      $line =~ s/\n\Z//s;
      ($oid, $value) = ($line =~ /([^\s]+)\s+(.*)/s);
      $line = "";
      push @varbindings, [$oid, $value];
  }

  # Notice the assembled varbindings slightly differs from that in embperl. 
  # For instance, hex string is surrounded by doubly quote, and never
  # prefixed by "Hex-STRING: ".
  return (\%pdu_info, \@varbindings);
}

# traphandle handler
sub handle_trap {
  chomp(my @stdin = <STDIN>);
  logger("traphandle", "input text is ", \@stdin);
  my ($pdu_info, $varbindings) = get_from_stdin(\@stdin);
  logger("traphandle", "got pdu_info and varbindings ", [$pdu_info,$varbindings]);
  process($pdu_info, $varbindings);

  my $laps = $perf->laps;
  logger("perf", join(", ", map { sprintf '%s=%f', $_,$laps->{$_} } keys %{$laps}));
  $perf->reset;
}

# alert dispatcher
sub alert {
  my ($pdu_info, $uptime, $event) = @_;

  if ($opts{'alert'} eq 'email') {
    my $data = mail_data($alert_opts{'from'}, \@ARGV, $pdu_info, $uptime, $event);
    logger("alert", "mail data is", [\$data]);

    if ($alert_prog) {
      logger("alert", "mailer invoked with ", [$alert_prog,\@ARGV]);
      $perf->start;
      if (open MAILER, "|-", $alert_prog, @ARGV) {
        print MAILER $data;
        close MAILER;
      }
      else {
        logger("warn", "Unable to alert through mailer[$alert_prog @ARGV]: $!");
      }
      $perf->stop("mailer");
    }
    else {
      logger("alert", "mail by Net::SMTP ", [$alert_opts{'server'},$alert_opts{'from'}, \@ARGV]);
      $perf->start;
      eval {
        my $message = Net::SMTP->new($alert_opts{'server'}) || die "ERROR: can't talk to server $alert_opts{'server'}\n";
        $message->mail($alert_opts{'from'});
        $message->to(@ARGV) || die "ERROR: failed to send to the recepients ",join(",",@ARGV),": $!";
        $message->data();
        $message->datasend($data);
        $message->dataend();
        $message->quit;
      };
      $perf->stop("netsmtp");
      if ($@) {
        logger("warn", "alert mail failure ", $@);
      }
    }
  }
  elsif ($opts{'alert'} eq 'nagios') {
    my $command_file = $ARGV[0];
    logger("alert", "nagios external command file is $command_file");

    my $t = pettime($event);
    my ($code,$plugin_output) = nagios_check($event);
    my $nagios_host = nagios_host($pdu_info, $alert_opts{host});
    my $nagios_service = $alert_opts{service};

    # http://nagios.sourceforge.net/docs/3_0/extcommands.html
    my $cmd = "[$t] PROCESS_SERVICE_CHECK_RESULT;$nagios_host;$nagios_service;$code;$plugin_output";
    logger("alert", "nagios command is", $cmd);

    $perf->start;
    if (open NAGIOS, ">>", $command_file) {
      print NAGIOS "$cmd\n";
      close NAGIOS;
    }
    else {
      logger("warn", "nagios failure with $command_file: $!");
    }
    $perf->stop("nagios");
  }
  elsif ($opts{'alert'} eq 'nsca') {
    logger("alert", "send_nsca invoked as ", [$alert_prog, \@ARGV]);

    my ($code,$plugin_output) = nagios_check($event);
    my $nagios_host = nagios_host($pdu_info, $alert_opts{host});
    my $nagios_service = $alert_opts{service};

    # http://nagios.sourceforge.net/download/contrib/documentation/misc/NSCA_Setup.pdf
    my $cmd= "$nagios_host\t$nagios_service\t$code\t$plugin_output";
    logger("alert", "nsca command is", $cmd);

    $perf->start;
    if (open NSCA, "|-", $alert_prog, @ARGV) {
      print NSCA "$cmd\n";
      close NSCA;
      if ($? >> 8) {
        logger("warn", "nsca failure with CHILD_ERROR: $?");
      }
    }
    else {
      logger("warn", "nsca failure: $!");
    }
    $perf->stop("nsca");
  }
  elsif ($opts{'alert'} eq 'noop') {
    logger('alert', 'noop alert selected');
  }
  else {
    logger("alert", "alert module");
    # TODO module
    die "alert module is not implemented!";
  }
}

# load sdr cache config into global mapping hash
sub load_sdrcache_config {
  my ($conf) = @_;

  my $cache_file = "";
  my $nl = 0;
  for (@{$conf}) {
    $nl++;
    chomp;
    s/#.*$//; # trim comment
    s/\s+$//; # trim trailing whitespaces
    next if /^$/;
    if (/^\S/) {
      if (-e $_) {
        $cache_file = $_;
      }
      else {
        return "ERROR: no such sdr cache file[$_] at line #$nl";
      }
    }
    if (/^\s/) {
      s/^\s+//; # trim leading whitespaces
      if ($cache_file) {
        for (split /\s+/) {
          $cache_mapping{$_} = $cache_file;
        }
      }
      else {
        return "ERROR: missing sdr cache file for host[$_] at line #$nl";
      }
    }
  }

  return;
}

# given an ipv4 address, resolve to related sdr cache
sub resolve_sdrcache {
  my ($ipmi_node) = @_;
  my $sdrcache = "";
  if (exists $cache_mapping{$ipmi_node}) {
     $sdrcache = $cache_mapping{$ipmi_node};
     logger("sdrcache", "$ipmi_node resolved to $sdrcache");
  }
  else {
     my $re = qr/^(.*)\[([-\d,]+)\](.*)$/;  # to match against eg. 10.2.3.[4-7]
     for my $k (keys %cache_mapping) {
        if (my ($prefix,$range,$suffix) = ($k =~ m/$re/)) {
           if (my ($item) = ($ipmi_node =~ /^\Q$prefix\E(.+)\Q$suffix\E$/)) {
              for (split /,+/, $range) {
                 my ($f,$t);
                 if (
                      ((($f,$t) = m/^(\d+)-(\d+)$/) && $f <= $item && $item <= $t)
                      || $item == $_
                    ) {
                    # got it
                    $sdrcache = $cache_mapping{$k};
                    logger("sdrcache", "$ipmi_node resolved to ", [$k => $sdrcache]);
                 }
              }
           }
        }
     }
  }

  $sdrcache || logger("sdrcache", "$ipmi_node will use default cache");

  return $sdrcache;
}

# process and verify args
sub process_args {
  # parse global ARGV for this package
  GetOptions(\%opts, 'help!', 'quiet!', 'mode|m=s', 'ack!', 'workaround|W=s',
    'trapoid|o=s', 'sdrcache|c=s', 'log|f=s', 'Debug|D=s', 'alert|n=s');

  if ($opts{'help'}) {
    usage();
  }

  # log file
  if ($opts{'log'}) {
    if (-w $opts{'log'}) {
      $log_filename = $opts{'log'};
    }
    else {
      die "log file $opts{'log'} is not writable";
    }
  }
  unless ($opts{'quiet'}) {
    print STDERR "petalert.pl is logging to $log_filename, use -q to suppress this tip\n";
  }

  # comma-separted debug tokens
  if ($opts{'Debug'}) {
    $logger_token{$_} = 1 for split /,+/, $opts{'Debug'};
  }
  # logging now ready
  logger("argv", "parsed options is ", \%opts);

  if ($opts{'sdrcache'}) {
    my $conf = $opts{'sdrcache'};
    logger("sdrcache", "config is [$conf]");

    open CONF, "<", $conf || logger("warn", "assumes default cache because failed to config file[$conf]: $!");
    chomp(my @lines = <CONF>);
    close CONF;

    load_sdrcache_config(\@lines);
    logger("sdrcache", "cache_mapping is ", \%cache_mapping);

    if ($opts{'syntax-only'}) {
      exit;
    }
  }

  if ($opts{'mode'} eq 'embperl') {
    unless (exists $opts{trapoid}) {
      $opts{trapoid} = "all";
      logger("argv", "no trapoid specified, defaults to all");
    }
    require NetSNMP::TrapReceiver;
  }
  elsif ($opts{'mode'} eq 'traphandle') {
  }
  else {
    print STDERR "Unknown operation mode: $opts{mode}\n";
    usage();
  }

  # alert method defaults to no-op
  unless (exists $opts{'alert'}) {
    $opts{'alert'} = 'noop';
    logger("argv", "no alert method specified, defaults to noop");
  }

  # alert methods
  if ($opts{'alert'} eq 'email') {
    # use external mail program
    if ($ARGV[0] && $ARGV[0] eq "--prog") {
      shift @ARGV;
      $alert_prog = shift @ARGV;
      unless (-x $alert_prog) {
        die "mailer[$alert_prog] is not executable\n";
      }
    }
    # or use perl module
    else {
      GetOptions(\%alert_opts, "server=s", "from=s");
      require Net::SMTP;
    }
  }
  elsif ($opts{'alert'} eq 'nagios' || $opts{'alert'} eq 'nsca') {
    GetOptions(\%alert_opts, "prog=s", "host|H=s", "service|S=s");
    $alert_opts{host} ||= "short";
    $alert_opts{service} ||= "PET";
    if ($alert_opts{host} ne "fqdn" && $alert_opts{host} ne "short") { # TODO
      die "Unknown host mapping $alert_opts{host}\n";
    }
    if ($opts{'alert'} eq 'nagios' && !($ARGV[0] && -w $ARGV[0])) {
      die "nagios external command file[$ARGV[0]] is not writable\n";
    }
    if ($opts{'alert'} eq 'nsca' && ! $alert_opts{prog}) {
      die "send_nsca binary is not set\n";
    }
    $alert_prog = $alert_opts{prog} || "";
  }
  elsif ($opts{'alert'} eq 'noop') {
  }
  else {
    my $module = $opts{'alert'};
    if (-r $module) {
      require "$module";
      # TODO
      die "<not implemenented yet>";
    }
    else {
      die "Unknown alert module to load: $module\n";
    }
    # invokes handler
  }

  # @ARGV now holds alert specific arguments
}

sub main {
  @ARGV = @_;  # set global ARGV for this package
  process_args();
  $perf = IpmiPET::Perf->new;
  if ($opts{'mode'} eq 'traphandle') {
    logger("main", "running as traphandle");
    handle_trap();
  }
  elsif ($opts{'mode'} eq 'embperl') {
    logger("main", "running as embperl");
    NetSNMP::TrapReceiver::register($opts{trapoid}, \&my_receiver) ||
           warn "failed to register our perl trap handler\n";
  }
  else {
    die "Should never reach here!\n";
  }

  return 0;
}


# run the program
if ( !caller ) { exit main(@ARGV); }

1;
