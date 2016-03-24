#!/usr/bin/perl
#############################################################################
# Copyright (C) 2003-2009 FreeIPMI Core Team
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
# nagios_ipmi_sensors.pl
#
# Author: 
#
# Albert Chu <chu11 at llnl dot gov>
#
# Description:
#
# This script can be used to monitor IPMI sensors in nagios via
# FreeIPMI's ipmi-sensors.
#
# This tool will monitor the sensor state (Nominal, Warning, or
# Critical) of each sensor as determined by libfreeipmi's interpret
# library.  The Nominal, Warning, and Critical states of each sensor
# will be collected and counted.  The overall IPMI sensor status will
# be mapped into a Nagios status of OK, Warning, or Critical.  Details
# will then be output for Nagios to read.  See ipmi-sensors(8) for
# more general info on ipmi-sensors and
# freeipmi_interpret_sensors.conf(5) for more information on sensor
# states.
#
# Options:
#
# -h - specify hostname(s) to remotely access (don't specify for inband)
# -S - specify an alternate ipmi_sensors location
# -s - specify additional ipmi_sensors arguments
# -d - print debug info
# -H - output help
#
# Environment Variables:
#
# IPMI_HOSTS - specify hostname(s) to remotely access (don't specify for inband)
# IPMI_SENSORS_PATH - specify an alternate ipmi-ssensors location
# IPMI_SENSORS_ARGS - specify additional ipmi-sensors arguments
#
# Setup Notes:
#
# Specify the remote hosts you wish to access IPMI information from
# via the -h option or IPMI_HOSTS environment variable.  If you wish
# only to monitor the local node, do not specify an ipmi host.  The
# input to the -h option is passed directly to ipmimonitoring.  So you
# may specify anything the ipmimonitoring tool accepts including
# hostranged (e.g. foo[0-127]) or comma separated
# (e.g. foo0,foo1,foo2,foo3) inputs.  If you wish to monitor both
# remote and local system, remember to specify one of the hosts as
# "localhost".  Most will probably want to monitor just one host (get
# the IPMI status for each individual machine being monitored),
# however more than one host can be analyzed for a collective result.
#
# If stored in a non-default location the -S option or
# IPMI_SENSORS_PATH environment variable must be specified to
# determine the ipmimonitoring location.
#
# In order to specify non-defaults for ipmimonitoring use the -s
# argument or IPMI_SENSORS_ARGS environment variable.  Typically,
# this option is necessary for non-default communication information
# or authentication information (e.g. driver path, driver type,
# username, password, etc.).  Non-default communication information
# can also be stored in the FreeIPMI configuration file.  This is the
# suggested method because passwords and other sensitive information
# could show up in ps(1).  If you wish to limit the sensors being
# monitored, you can also specify which record-ids are to be monitored
# (-s option).
#
# The setup for this can vary depending on your environment and nagios
# setup, but most will need to set this up in nagios by defining a
# command and then a service.
#
# define command  {
#    command_name nagios_ipmi_sensors
#    command_line /path/nagios_ipmi_sensors.pl -h $ARG1$
# }
#
# define service {
#    host_name           foohost
#    service_description ipmi
#    check_command       nagios_ipmi_sensors!foohost
# }
#
# The default session timeout length in ipmi-sensors is 20 seconds.
# We would recommend that IPMI not be monitored more frequently than
# that.
#
# Help:
# 
# Report bugs to freeipmi-users@gnu.org or freeipmi-devel@gnu.org.
#
#############################################################################

use strict;

use Getopt::Std;

my $debug = 0;

my $IPMI_HOSTS = undef;
my $IPMI_SENSORS_PATH = "/usr/sbin/ipmi-sensors";
my $IPMI_SENSORS_ARGS = "";

my $IPMI_SENSORS_OUTPUT;
my @IPMI_SENSORS_OUTPUT_LINES;
my $line;

my $cmd;

my $num_output = 0;
my $warning_num = 0;
my $critical_num = 0;
my $fatal_error = 0;

sub usage
{
    my $prog = $0;
    print "Usage: $prog [-h <hostname(s)>] [-S <path>] [-s <sensors arguments>] [-d] [-H]\n";
    print "  -h specify hostname(s) to remotely access\n";
    print "  -S specify an alternate ipmi-sensors path\n";
    print "  -s specify additional ipmi-sensors arguments\n";
    print "  -d print debug info\n";
    print "  -H output help\n";
    exit 0;
}

if (!getopts("h:S:s:dH"))
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

if (defined($main::opt_S))
{
    $IPMI_SENSORS_PATH = $main::opt_S;
}

if (defined($main::opt_s))
{
    $IPMI_SENSORS_ARGS = $main::opt_s;
}

if (defined($main::opt_d))
{
    $debug = 1;
}

if ($ENV{"IPMI_HOSTS"})
{
    $IPMI_HOSTS = $ENV{"IPMI_HOSTS"};
}

if ($ENV{"IPMI_SENSORS_PATH"})
{
    $IPMI_SENSORS_PATH = $ENV{"IPMI_SENSORS_PATH"};
}

if ($ENV{"IPMI_SENSORS_ARGS"})
{
    $IPMI_SENSORS_ARGS = $ENV{"IPMI_SENSORS_ARGS"};
}

if ($debug)
{
    print "IPMI_HOSTS=$IPMI_HOSTS\n";
    print "IPMI_SENSORS_PATH=$IPMI_SENSORS_PATH\n";
    print "IPMI_SENSORS_ARGS=$IPMI_SENSORS_ARGS\n";
}

if (!(-x $IPMI_SENSORS_PATH))
{
    print "$IPMI_SENSORS_PATH cannot be executed\n";
    exit(1);
}

# note, don't need --ignore-non-interpretable-sensors, legacy output handles it
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

    my $output_str;

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
        $fatal_error++;
        next;
    }

    # make name better, convert spaces and slashes into underscores
    $id_string =~ s/ /_/g;
    $id_string =~ s/\//_/g;

    if ($state eq "Nominal") 
    {
        next;
    }

    if ($state eq "N/A")
    {
        next;
    }

    if ($state eq "Warning")
    {
        $warning_num++;
        $output_str = "WARNING";
    }
    elsif ($state eq "Critical")
    {
        $critical_num++;
        $output_str = "CRITICAL";
    }
    else
    {
        print "State not parsable\n";
        $fatal_error++;
        next;
    } 

    if ($num_output)
    {
        print "; ";
    }
    print "$id_string - $output_str";
    $num_output++;
}

# Nagios Exit Codes
# 0 = OK
# 1 = WARNING
# 2 = CRITICAL
# 3 = UNKNOWN

if ($fatal_error)
{
    exit 3;                     
}

if ($critical_num)
{
    exit 2;
}

if ($warning_num)
{
    exit 1;
}

exit 0;
