<?php
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';
$cmd = "/usr/bin/ipmitool sel ".$_GET["options"].$ipmitool_options;
exec($cmd);
?>
