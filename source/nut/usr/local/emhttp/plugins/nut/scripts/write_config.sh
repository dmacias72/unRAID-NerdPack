#!/bin/bash
#
# NUT plugin configuration script for unRAID
# By macester macecapri@gmail.com
#
NUTCFG=/boot/config/plugins/nut/nut.cfg


# Killpower flag permissions
chmod 777 /etc/ups/flag

# Add nut user and group for udev at shutdown
GROUP=$( grep -ic "218" /etc/group )
USER=$( grep -ic "218" /etc/passwd )

if [ $GROUP -ge 1 ]; then
    echo "NUT Group already configured"
else
    groupadd -g 218 nut
fi

if [ $USER -ge 1 ]; then
    echo "NUT User already configured"
else
    useradd -u 218 -g nut -s /bin/false nut
fi

# Nut config files

# Add the driver config
driver_custom=$( grep -ic 'DRIVER="custom"' $NUTCFG )
if [ $driver_custom -eq 1 ]; then
        var1=$( grep -i "SERIAL=" $NUTCFG|cut -d \" -f2|sed 's/^/driver = /' )
        sed -i "2 s/.*/$var1/" /etc/ups/ups.conf
else
        var2=$( grep -i "DRIVER=" $NUTCFG|cut -d \" -f2|sed 's/^/driver = /' )
        sed -i "2 s/.*/$var2/" /etc/ups/ups.conf
fi

# add the port
var3=$( grep -i "PORT=" $NUTCFG|cut -d \" -f2|sed 's/^/port = /' )
sed -i "3 s~.*~$var3~" /etc/ups/ups.conf

# add mode standalone/netserver
var4=$( grep -i "MODE=" $NUTCFG|cut -d \" -f2|sed 's/^/MODE=/' )
sed -i "1 s/.*/$var4/" /etc/ups/nut.conf

# Set which shutdown script NUT should use
mode_bat_level=$( grep -ic 'SHUTDOWN="batt_level"' $NUTCFG )
mode_bat_timer=$( grep -ic 'SHUTDOWN="batt_timer"' $NUTCFG )

if [ $mode_bat_level -eq 1 ]; then
        sed -i "6 s,.*,NOTIFYCMD \"/usr/local/emhttp/plugins/nut/scripts/notifycmd_batterylevel\"," /etc/ups/upsmon.conf
else
  if [ $mode_bat_timer -eq 1 ]; then
        sed -i "6 s,.*,NOTIFYCMD \"/usr/local/emhttp/plugins/nut/scripts/notifycmd_seconds\"," /etc/ups/upsmon.conf
  else
        sed -i "6 s,.*,NOTIFYCMD \"/usr/local/emhttp/plugins/nut/scripts/notifycmd_timeout\"," /etc/ups/upsmon.conf
  fi
fi

# Edit timers fo shutdown scripts

# shutdown when battery gets to level
var5=$( grep -i "BATTERYLEVEL=" $NUTCFG|cut -d \" -f2|sed 's/^/BATTERYLEVEL=/' )
sed -i "6 s/.*/$var5/" /usr/local/emhttp/plugins/nut/scripts/notifycmd_batterylevel

# shutdown when battery time runs out
var6=$( grep -i "SECONDS=" $NUTCFG|cut -d \" -f2|sed 's/^/SECONDS=/' )
sed -i "6 s/.*/$var6/" /usr/local/emhttp/plugins/nut/scripts/notifycmd_seconds

# shutdown on user timer
var7=$( grep -i "TIMEOUT=" $NUTCFG|cut -d \" -f2|sed 's/^/TIMEOUT=/' )
sed -i "6 s/.*/$var7/" /usr/local/emhttp/plugins/nut/scripts/notifycmd_timeout

# Set if the ups should be turned off
ups_kill=$( grep -ic 'UPSKILL="enable"' $NUTCFG )
if [ $ups_kill -eq 1 ]; then
    var8='POWERDOWNFLAG /etc/ups/flag/killpower'
    sed -i "3 s,.*,$var8," /etc/ups/upsmon.conf
else
    var9='POWERDOWNFLAG /etc/ups/flag/no_killpower'
    sed -i "3 s,.*,$var9," /etc/ups/upsmon.conf
fi

# Link shutdown scripts for poweroff in rc.0 and rc.6
UDEV=$( grep -ic "/usr/local/emhttp/plugins/nut/scripts/nut_restart_udev" /etc/rc.d/rc.6 )
if [ $UDEV -ge 1 ]; then
    echo "UDEV lines already exist in rc.0,6"
else
    sed -i '/\/bin\/mount -v -n -o remount,ro \//r /usr/local/emhttp/plugins/nut/scripts/txt/udev.txt' /etc/rc.d/rc.6
fi

KILL=$( grep -ic "/usr/local/emhttp/plugins/nut/scripts/nut_kill_inverter" /etc/rc.d/rc.6 )
if [ $KILL -ge 1 ]; then
    echo "KILL_INVERTER lines already exist in rc.0,6"
else
     sed -i -e '/# Now halt (poweroff with APM or ACPI enabled kernels) or reboot./r /usr/local/emhttp/plugins/nut/scripts/txt/kill.txt' -e //N /etc/rc.d/rc.6
fi
