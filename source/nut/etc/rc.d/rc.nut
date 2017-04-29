#!/bin/sh
# Slackware startup script for Network UPS Tools
# Copyright 2010 V'yacheslav Stetskevych
# Edited for unRAID by macester macecapri@gmail.com

DPATH=/usr/bin
FILE=/boot/config/plugins/nut/nut.cfg
export PATH=$DPATH:$PATH



start_driver() {
       /usr/sbin/upsdrvctl -u root start || exit 1
}

start_upsd() {
        /usr/sbin/upsd -u root || exit 1
}

start_upsmon() {
        /usr/sbin/upsmon -u root || exit 1
}

stop() {
        echo "Stopping the UPS services... "
        if pgrep upsd 2>&1 >/dev/null; then
                /usr/sbin/upsd -c stop; fi
        if pgrep upsmon 2>&1 >/dev/null; then
                /usr/sbin/upsmon -c stop; fi
        /usr/sbin/upsdrvctl stop
        sleep 2
        if [ -f /var/run/upsmon.pid ]; then
                  rm /var/run/upsmon.pid; fi
}

write_config() {
        /usr/local/emhttp/plugins/nut/scripts/write_config.sh
}

case "$1" in
        start)  # starts everything (for a ups server box)
               sleep 1
               write_config
               sleep 3
               start_driver
               start_upsd
               start_upsmon
                ;;
        start_upsmon) # starts upsmon only (for a ups client box)
                start_upsmon
                ;;
        stop) # stops all UPS-related daemons
                stop
                ;;
        shutdown) # shuts down the UPS
                echo "Killing inverter..."
                /usr/sbin/upsdrvctl shutdown
                ;;
        reload)
                write_config
                /usr/sbin/upsd -c reload
                /usr/sbin/upsmon -c reload
                ;;
	write_config)
                write_config
                ;;
        *)
                echo "Usage: $0 {start|start_upsmon|stop|shutdown|reload|restart|write_config}"
esac
