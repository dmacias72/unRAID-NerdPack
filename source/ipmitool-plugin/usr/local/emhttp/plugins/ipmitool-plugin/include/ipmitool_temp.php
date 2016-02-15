<?
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';

function format_ipmi_temp($reading, $unit, $dot) {
  return ($reading>0 ? ($unit=='F' ? round(9/5*$reading+32) : str_replace('.',$dot,$reading)) : '##')."&thinsp;$unit";
}

if ($ipmi_cpu_temp || $ipmi_mb_temp || $ipmi_fan_disp){
	$ipmi_readings = ipmi_get_reading([$ipmi_cpu_temp, $ipmi_mb_temp, $ipmi_fan_disp], $ipmi_options);
	$ipmi_temps = [];

	if ($ipmi_readings[$ipmi_cpu_temp])
		$ipmi_temps[] = "<img src='/plugins/$plugin/icons/cpu.png' title='$ipmi_cpu_temp' class='icon'>".format_ipmi_temp($ipmi_readings[$ipmi_cpu_temp], $_GET['unit'], $_GET['dot']);

	if ($ipmi_readings[$ipmi_mb_temp])
		$ipmi_temps[] = "<img src='/plugins/$plugin/icons/mb.png' title='$ipmi_mb_temp' class='icon'>".format_ipmi_temp($ipmi_readings[$ipmi_mb_temp], $_GET['unit'], $_GET['dot']);

	if ($ipmi_readings[$ipmi_fan_disp])
		$ipmi_temps[] = "<img src='/plugins/$plugin/icons/fan.png' title='$ipmi_fan_disp' class='icon'>".$ipmi_readings[$ipmi_fan_disp]."&thinsp;rpm";
}
if ($ipmi_temps)
	echo "<span id='temps' style='margin-right:16px'>".implode('&nbsp;', $ipmi_temps)."</span>";
?>