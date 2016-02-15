<?php
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';
echo json_encode(ipmi_sensors($ipmi_options));
?>