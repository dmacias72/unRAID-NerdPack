<?
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';

function ipmi_temp($reading, $unit, $dot) {
  return ($reading>0 ? ($unit=='F' ? round(9/5*$reading+32) : str_replace('.',$dot,$reading)) : '##')."&thinsp;$unit";
}

if ($cpu_temp || $mb_temp || $fan_disp){
	$readings = ipmi_get_reading([$cpu_temp, $mb_temp, $fan_disp], $options);
	$temps = [];

	if ($readings[$cpu_temp])
		$temps[] = "<img src='/plugins/$plugin/icons/cpu.png' title='$cpu_temp' class='icon'>".ipmi_temp($readings[$cpu_temp], $_GET['unit'], $_GET['dot']);

	if ($readings[$mb_temp])
		$temps[] = "<img src='/plugins/$plugin/icons/mb.png' title='$mb_temp' class='icon'>".ipmi_temp($readings[$mb_temp], $_GET['unit'], $_GET['dot']);

	if ($readings[$fan_disp])
		$temps[] = "<img src='/plugins/$plugin/icons/fan.png' title='$fan_disp' class='icon'>".$readings[$fan_disp]."&thinsp;rpm";
}
if ($temps)
	echo "<span id='temps' style='margin-right:16px'>".implode('&nbsp;', $temps)."</span>";
?>