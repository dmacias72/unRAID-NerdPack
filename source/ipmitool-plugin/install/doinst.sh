#!/bin/sh
RC_SCRIPT="/etc/rc.d/rc.ipmievd"
RC_SCRIPT2="/etc/rc.d/rc.ipmitail"
SD_RCFILE="/etc/rc.d/rc.local_shutdown"

# Update file permissions of scripts
chmod +0755 /usr/local/emhttp/plugins/ipmitool-plugin/scripts/* \
 /usr/sbin/ipmitail \
 /usr/sbin/ipmifan \
 $RC_SCRIPT \
 $RC_SCRIPT2

###Stop Scripts###

# Add stop script to rc.local_shutdown script	
if ! grep "$RC_SCRIPT" $SD_RCFILE >/dev/null 2>&1
	then echo -e "\n[ -x $RC_SCRIPT ] && $RC_SCRIPT stop" >> $SD_RCFILE
fi
[ ! -x $SD_RCFILE ] && chmod u+x $SD_RCFILE

# Add stop script to rc.local_shutdown script
if ! grep "$RC_SCRIPT2" $SD_RCFILE >/dev/null 2>&1
	then echo -e "\n[ -x $RC_SCRIPT2 ] && $RC_SCRIPT2 stop" >> $SD_RCFILE
fi
[ ! -x $SD_RCFILE ] && chmod u+x $SD_RCFILE