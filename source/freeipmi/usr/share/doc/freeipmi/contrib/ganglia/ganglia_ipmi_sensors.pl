#!/usr/bin/perl
#############################################################################
# Copyright (C) 2003-2010 FreeIPMI Core Team
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################
#
# ganglia_ipmi_sensors.pl
#
# Author: 
#
# Albert Chu <chu11 at llnl dot gov>
#
# Description:
#
# This script can be used to monitor IPMI sensors in ganglia via
# FreeIPMI's ipmi-sensors.
#
# By default, this tool will monitor the sensor state (Nominal,
# Warning, or Critical) of each sensor as determined by libfreeipmi's
# interpret library and the sensor readings of temperature, fan and
# voltage sensors.  See ipmi-sensors(8) for more general info on
# ipmi-sensors and freeipmi_interpret_sensors.conf(5) for more
# information on sensor states.
#
# Options:
#
# -h - specify hostname(s) to remotely access (don't specify for inband)
# -r - specify search and replace substitution expressions (separated by a colon) to
#      modify a hostname before being passed to gmetric.  This is useful if
#      the IPMI hostname differs from the desired hostname to input to gmetric.
#      For example "ipmi:my" would turn "ipmihost4" into "myhost4".  Not specifying
#      a colon results in a degenerate string removal.  For example,
#      "-ipmi" would turn "host4-ipmi" into "host4".
# -S - specify an alternate ipmi-sensors location
# -s - specify additional ipmi-sensors arguments
# -G - specify an alternate gmetric location
# -g - specify additional gmetric arguments
# -d - print debug info
# -D - do not send sensor data to ganglia (useful during debugging)
# -H - output help
#
# Environment Variables:
#
# IPMI_HOSTS - specify hostname(s) to remotely access (don't specify for inband)
# IPMI_HOSTS_SUBST - specify search and replace substitution
#                    expressions (separated by a colon) to modify a
#                    hostname before being passed to gmetric.  This is
#                    useful if the IPMI hostname differs from the
#                    desired hostname to input to gmetric.
# IPMI_SENSORS_PATH - specify an alternate ipmi-sensors location
# IPMI_SENSORS_ARGS - specify additional ipmi-sensors arguments
# GMETRIC_PATH - specify an alternate gmetric location
# GMETRIC_ARGS - specify additional gmetric arguments
#
# Setup Notes:
#
# Specify the remote hosts you wish to access IPMI information from
# via the -h option or IPMI_HOSTS environment variable.  If you wish
# only to monitor the local node, do not specify an ipmi host.  The
# input to the -h option is passed directly to ipmi-sensors.  So you
# may specify anything the ipmi-sensors tool accepts including
# hostranged (e.g. foo[0-127]) or comma separated
# (e.g. foo0,foo1,foo2,foo3) inputs.  If you wish to monitor both
# remote and local system, remember to specify one of the hosts as
# "localhost".
#
# If stored in a non-default location the -S option or
# IPMI_SENSORS_PATH environment variable must be specified to
# determine the ipmi-sensors location.
#
# If stored in a non-default location the -G option or GMETRIC_PATH
# environment variable must be specified to determine the gmetric
# location.
#
# In order to specify non-defaults for ipmi-sensors use the -s
# argument or IPMI_SENSORS_ARGS environment variable.  Typically,
# this option is necessary for non-default communication information
# or authentication information (e.g. driver path, driver type,
# username, password, etc.).  Non-default communication information
# can also be stored in the FreeIPMI configuration file.  This is the
# suggested method because passwords and other sensitive information
# could show up in ps(1).  If you wish to limit the sensors being
# monitored, you can also specify which record-ids are to be monitored
# (-r option).
#
# In order to specify non-defaults for gmetric, use the -g argument
# or GMETRIC_ARGS environment variable.  Typically, this option is
# necessary for non-default gmond.conf paths (i.e. -c
# /myspecial/gmond.conf).
#
# Most users will want to set this script to execute in cron(8).
# Using cron you may monitor at whatever interval you wish.  The
# recommended interval should be atleast longer than 20 seconds, since
# that is the default session timeout length.  
#
# Help:
# 
# Report bugs to freeipmi-users@gnu.org or freeipmi-devel@gnu.org.
#
#############################################################################

use strict;

use Getopt::Std;

use Socket;

my $no_sensor_state = 0;
my $no_sensor_readings = 0;
my $debug = 0;
my $no_ganglia = 0;

my $IPMI_HOSTS = undef;
my $IPMI_HOSTS_SUBST = undef;
my $IPMI_SENSORS_PATH = "/usr/sbin/ipmi-sensors";
my $IPMI_SENSORS_ARGS = "";
my $GMETRIC_PATH = "/usr/bin/gmetric";
my $GMETRIC_ARGS = "";
my $IPMI_SENSORS_EXTRA_ARGS = "";

my $IPMI_SENSORS_OUTPUT;
my @IPMI_SENSORS_OUTPUT_LINES;
my $line;

my $cmd;
my @subst;

sub usage
{
    my $prog = $0;
    print "Usage: $prog [-h <hostname(s)>] [-r <string>] [-S <path>] [-s <sensors arguments>] [-G <path>] [-g <arguments>] [-T] [-t] [-d] [-H]\n";
    print "  -h specify hostname(s) to remotely access\n";
    print "  -r specify search and replace substitution expressions on the hostname (e.g. 'ipmi:host')\n";
    print "  -S specify an alternate ipmi-sensors path\n";
    print "  -s specify additional ipmi-sensors arguments\n";
    print "  -G specify an alternate gmetric path\n";
    print "  -g specify additional gmetric arguments\n";
    print "  -T do not monitor sensor state\n";
    print "  -t do not monitor sensor readings\n";
    print "  -d print debug info\n";
    print "  -D do not send sensor data to ganglia (useful during debugging)\n";
    print "  -H output help\n";
    exit 0;
}

if (!getopts("h:r:S:s:G:g:TtdDH"))
{
    usage();
}

if (defined($main::opt_H))
{
    usage();
}

if (defined($main::opt_h))
{
    $IPMI_HOSTS = $main::opt_h;
}

if (defined($main::opt_r))
{
    $IPMI_HOSTS_SUBST = $main::opt_r;
}

if (defined($main::opt_S))
{
    $IPMI_SENSORS_PATH = $main::opt_S;
}

if (defined($main::opt_s))
{
    $IPMI_SENSORS_ARGS = $main::opt_s;
}

if (defined($main::opt_G))
{
    $GMETRIC_PATH = $main::opt_G;
}

if (defined($main::opt_g))
{
    $GMETRIC_ARGS = $main::opt_g;
}

if (defined($main::opt_T))
{
    $no_sensor_state = 1;
}

if (defined($main::opt_t))
{
    $no_sensor_readings = 1;
}

if (defined($main::opt_d))
{
    $debug = 1;
}

if (defined($main::opt_D))
{
    $no_ganglia = 1;
}

if ($ENV{"IPMI_HOSTS"})
{
    $IPMI_HOSTS = $ENV{"IPMI_HOSTS"};
}

if ($ENV{"IPMI_HOSTS_SUBST"})
{
    $IPMI_HOSTS_SUBST = $ENV{"IPMI_HOSTS_SUBST"};
}

if ($ENV{"IPMI_SENSORS_PATH"})
{
    $IPMI_SENSORS_PATH = $ENV{"IPMI_SENSORS_PATH"};
}

if ($ENV{"IPMI_SENSORS_ARGS"})
{
    $IPMI_SENSORS_ARGS = $ENV{"IPMI_SENSORS_ARGS"};
}

if ($ENV{"GMETRIC_PATH"})
{
    $GMETRIC_PATH = $ENV{"GMETRIC_PATH"};
}

if ($ENV{"GMETRIC_ARGS"}) 
{
    $GMETRIC_ARGS = $ENV{"GMETRIC_ARGS"};
}

if ($debug)
{
    print "IPMI_HOSTS=$IPMI_HOSTS\n";
    print "IPMI_HOSTS_SUBST=$IPMI_HOSTS_SUBST\n";
    print "IPMI_SENSORS_PATH=$IPMI_SENSORS_PATH\n";
    print "IPMI_SENSORS_ARGS=$IPMI_SENSORS_ARGS\n";
    print "GMETRIC_PATH=$GMETRIC_PATH\n";
    print "GMETRIC_ARGS=$GMETRIC_ARGS\n";
}

if (!(-x $IPMI_SENSORS_PATH))
{
    print "$IPMI_SENSORS_PATH cannot be executed\n";
    exit(1);
}

if (!$no_ganglia)
{
    if (!(-x $GMETRIC_PATH))
    {
        print "$GMETRIC_PATH cannot be executed\n";
        exit(1);
    }
}

if ($no_sensor_state && $no_sensor_readings)
{
    print "Must monitor atleast sensor state or sensor readings\n";
    exit(1);
}

if ($IPMI_HOSTS)
{
    $cmd = "$IPMI_SENSORS_PATH $IPMI_SENSORS_ARGS -h $IPMI_HOSTS --quiet-cache --sdr-cache-recreate --always-prefix --no-header-output --output-sensor-state";
}
else
{
    $cmd = "$IPMI_SENSORS_PATH $IPMI_SENSORS_ARGS --quiet-cache --sdr-cache-recreate --always-prefix --no-header-output --output-sensor-state"
}

if ($debug)
{
    print "ipmi-sensors command: $cmd\n";
}

$IPMI_SENSORS_OUTPUT = `$cmd`;
if ($? != 0)
{
    print "$IPMI_SENSORS_PATH: exited with error\n";
}

@IPMI_SENSORS_OUTPUT_LINES = split(/\n/, $IPMI_SENSORS_OUTPUT);

foreach $line (@IPMI_SENSORS_OUTPUT_LINES)
{
    my $hostname;
    my $record_id;
    my $id_string;
    my $type;
    my $state;
    my $reading;
    my $units;
    my $event;
    my $id_string_state;

    my $ip_address;

    my $cmd_state;
    my $cmd_reading;

    if ($debug)
    {
        print "Parsing: $line\n";
    }

    if ($line =~ /(.+)\: (\d+)(\s+)\| (.+)(\s+)\| (.+)(\s+)\| (.+)(\s+)\| (.+)(\s+)\| (.+)(\s+)\| (.+)/)
    {
        $hostname = $1;
        $record_id = $2;
        $id_string = $4;
        $type = $6;
        $state = $8;
        $reading = $10;
        $units = $12;
        $event = $14;

        # trim whitespace off end of string
        $record_id =~ s/\s+$//;
        $id_string =~ s/\s+$//;
        $type =~ s/\s+$//;
        $state =~ s/\s+$//;
        $reading =~ s/\s+$//;
        $units =~ s/\s+$//;
    }
    else
    {
        print "Line not parsable\n";
        next;
    }

    # make name better, convert spaces and slashes into underscores
    $id_string =~ s/ /_/g;
    $id_string =~ s/\//_/g;
    
    if ($IPMI_HOSTS_SUBST) {
	@subst = split(/:/, $IPMI_HOSTS_SUBST);
	$hostname =~ s/$subst[0]/$subst[1]/;
    }

    if ($hostname ne "localhost" && $hostname ne "127.0.0.1")
    {
        my $packet_ip = gethostbyname($hostname);
        
        if (defined($packet_ip))
        {
            $ip_address = inet_ntoa($packet_ip);
        }
        else
        {
            print "Cannot resolve ip: $hostname\n";
            next;
        }
    }
   
    if (!$no_sensor_state)
    {
        if ($state ne "N/A")
        {
            $id_string_state = $id_string . "_State";
            if ($hostname ne "localhost" && $hostname ne "127.0.0.1")
            {
                $cmd_state = "$GMETRIC_PATH $GMETRIC_ARGS -n $id_string_state -v $state -t string -S $ip_address:$hostname";
            }
            else
            {
                $cmd_state = "$GMETRIC_PATH $GMETRIC_ARGS -n $id_string_state -v $state -t string";
            }
        }
    }

    if (!$no_sensor_readings)
    {
        if ((($type eq "Temperature"
	      && ($units eq "C"
		  || $units eq "F"))
             || ($type eq "Voltage"
		 && $units eq "V")
             || ($type eq "Fan"
		 && $units eq "RPM"))
            && $reading ne "N/A")
        {
            if ($hostname ne "localhost" && $hostname ne "127.0.0.1")
            {
                $cmd_reading = "$GMETRIC_PATH $GMETRIC_ARGS -n $id_string -v $reading -t double -u $units -S $ip_address:$hostname";
            }
            else
            {
                $cmd_reading = "$GMETRIC_PATH $GMETRIC_ARGS -n $id_string -v $reading -t double -u $units";
            }
        }
    }

    if ($debug)
    {
        if ($cmd_state)
        {
            print "gmetric command = $cmd_state\n";
        }
        if ($cmd_reading)
        {
            print "gmetric command = $cmd_reading\n";
        }
    }

    if (!$no_ganglia)
    {
        if ($cmd_state)
        {
            `$cmd_state`;
            if ($? != 0)
            {
                print "\"$cmd_state\": failed\n";
                exit(1);
            }
        }
        if ($cmd_reading)
        {
            `$cmd_reading`;
            if ($? != 0)
            {
                print "\"$cmd_reading\": failed\n";
                exit(1);
            }
        }
    }
}

