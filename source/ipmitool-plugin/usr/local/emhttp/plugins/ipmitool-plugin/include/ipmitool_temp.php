<?
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';

function my_temp($reading, $unit, $dot) {
  return ($reading>0 ? ($unit=='F' ? round(9/5*$reading+32) : str_replace('.',$dot,$reading)) : '##')."&thinsp;$unit";
}

$sensors_array = [];

if ($ipmitool_cpu){
	$ipmitool_cpu_temp = ipmi_get_reading($ipmitool_cpu, $ipmitool_options);
	if ($ipmitool_cpu_temp)
		$sensors_array[] = "<img src='/plugins/$plugin/icons/cpu.png' title='$ipmitool_cpu' class='icon'>".my_temp($ipmitool_cpu_temp, $_GET['unit'], $_GET['dot']);
}
if ($ipmitool_mb){
	$ipmitool_mb_temp = ipmi_get_reading($ipmitool_mb, $ipmitool_options);
	if ($ipmitool_mb_temp)
		$sensors_array[] = "<img src='/plugins/$plugin/icons/mb.png' title='$ipmitool_mb' class='icon'>".my_temp($ipmitool_mb_temp, $_GET['unit'], $_GET['dot']);
}
if ($ipmitool_fan){
	$ipmitool_fan_rpm = ipmi_get_reading($ipmitool_fan, $ipmitool_options);
	if ($ipmitool_fan_rpm)
		$sensors_array[] = "<img src='/plugins/$plugin/icons/fan.png' title='$ipmitool_fan' class='icon'>".$ipmitool_fan_rpm."&thinsp;rpm";
}
if ($sensors_array)
	echo "<span id='temps' style='margin-right:16px'>".implode('&nbsp;', $sensors_array)."</span>";
?>
