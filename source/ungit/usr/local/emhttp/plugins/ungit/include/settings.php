<?
$gcfg_file = '/boot/config/plugins/ungit/ungit.cfg';
if(file_exists($gcfg_file))
    $gcfg = parse_ini_file($gcfg_file);

$gdaemon = isset($gcfg['DAEMON']) ? $gcfg['DAEMON'] : "disable";
//$qipaddr = preg_match('/^(?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)(?:[.](?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)){3}$/', $ipmi_cfg['host']) ?
//    $qcfg['host'] : $var['IPADDR'];
$gipaddr = 'localhost';
$gport   = (isset($gcfg['PORT']) && is_numeric($gcfg['PORT']) && $gcfg['PORT'] > 0 && $gcfg['PORT'] < 65535 ) ? $gcfg['PORT'] : 8448;
$gversion = trim(shell_exec( 'ungit -v' ));

//check running status
$grunning = (trim(shell_exec( "[ -f /proc/`cat /var/run/ungit.pid 2> /dev/null`/exe ] && echo 1 || echo 0 2> /dev/null" )) == 1);
$daemon_running  = "<span class='green'>Running</span>";
$daemon_stopped  = "<span class='orange'>Stopped</span>";
$gstatus  = ($grunning) ? $daemon_running : $daemon_stopped;
?>