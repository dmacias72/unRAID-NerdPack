<?php
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';
echo json_encode(ipmi_events($ipmitool_options));
?>