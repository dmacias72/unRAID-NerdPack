<?php
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';

shell_exec("/usr/bin/ipmitool sel ".$_GET["options"].$ipmi_options);
?>