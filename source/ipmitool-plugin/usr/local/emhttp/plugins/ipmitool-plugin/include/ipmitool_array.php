<?php
$command = "/usr/bin/ipmitool ".$_POST["options"]." 2>/dev/null";
exec($command, $output);
$array = array();
for ($i = 0; $i < sizeof($output); $i++) {
	$value = explode(",", $output[$i]);
	$array[] = $value;
}
echo json_encode($array);
?>
