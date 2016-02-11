#!/bin/sh
RC_SCRIPT="/etc/rc.d/rc.shellinaboxd"
SD_RCFILE="/etc/rc.d/rc.local_shutdown"

# Update file permissions of scripts
chmod +0755 /usr/local/emhttp/plugins/shellinabox-plugin/scripts/* \
	/etc/rc.d/rc.shellinaboxd \
	/usr/sbin/screenfetch

# add stop to shutdown script	
if ! grep "$RC_SCRIPT" $SD_RCFILE >/dev/null 2>&1
	then echo -e "\n[ -x $RC_SCRIPT ] && $RC_SCRIPT shutdown" >> $SD_RCFILE
fi
[ ! -x $SD_RCFILE ] && chmod u+x $SD_RCFILE
