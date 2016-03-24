# Update the /usr/info/dir info-database, so that we will see the new
# "gmp" item in info root structure, if we type "info".
ErrCount=0

function echo_exit {
  ((ErrCount += $1))
  if [ $1 -eq 0 ]; then
    echo -n "$2 "
  else
    echo -n $3
  fi
}

if [ -x /usr/bin/install-info ] ; then
  echo -n "Installing info page... "
  install-info --info-dir=/usr/info /usr/info/freeipmi-faq.info.gz 2>/dev/null
  echo_exit $ErrCount "DONE" "FAILURE"
  echo
else
  echo "WARNING: Info pages cannot be installed!"
fi

( cd usr/sbin ; rm -rf rmcp-ping )
( cd usr/sbin ; ln -sf /usr/sbin/rmcpping rmcp-ping )
( cd usr/sbin ; rm -rf ipmi-power )
( cd usr/sbin ; ln -sf /usr/sbin/ipmipower ipmi-power )
( cd usr/sbin ; rm -rf ipmi-ping )
( cd usr/sbin ; ln -sf /usr/sbin/ipmiping ipmi-ping )
( cd usr/sbin ; rm -rf ipmi-detect )
( cd usr/sbin ; ln -sf /usr/sbin/ipmidetect ipmi-detect )
( cd usr/sbin ; rm -rf ipmi-console )
( cd usr/sbin ; ln -sf /usr/sbin/ipmiconsole ipmi-console )
( cd usr/sbin ; rm -rf pef-config )
( cd usr/sbin ; ln -sf /usr/sbin/ipmi-pef-config pef-config )
( cd usr/lib ; rm -rf libipmidetect.so )
( cd usr/lib ; ln -sf libipmidetect.so.0.0.0 libipmidetect.so )
( cd usr/lib ; rm -rf libipmidetect.so.0 )
( cd usr/lib ; ln -sf libipmidetect.so.0.0.0 libipmidetect.so.0 )
( cd usr/lib ; rm -rf libipmimonitoring.so )
( cd usr/lib ; ln -sf libipmimonitoring.so.5.0.6 libipmimonitoring.so )
( cd usr/lib ; rm -rf libipmimonitoring.so.5 )
( cd usr/lib ; ln -sf libipmimonitoring.so.5.0.6 libipmimonitoring.so.5 )
( cd usr/lib ; rm -rf libipmiconsole.so )
( cd usr/lib ; ln -sf libipmiconsole.so.2.3.2 libipmiconsole.so )
( cd usr/lib ; rm -rf libipmiconsole.so.2 )
( cd usr/lib ; ln -sf libipmiconsole.so.2.3.2 libipmiconsole.so.2 )
( cd usr/lib ; rm -rf libfreeipmi.so )
( cd usr/lib ; ln -sf libfreeipmi.so.17.0.0 libfreeipmi.so )
( cd usr/lib ; rm -rf libfreeipmi.so.17 )
( cd usr/lib ; ln -sf libfreeipmi.so.17.0.0 libfreeipmi.so.17 )
