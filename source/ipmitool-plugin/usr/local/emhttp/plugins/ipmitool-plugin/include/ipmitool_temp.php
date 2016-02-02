<?
require_once '/usr/local/emhttp/plugins/ipmitool-plugin/include/ipmitool_helpers.php';

function ipmi_temp($reading, $unit, $dot) {
  return ($reading>0 ? ($unit=='F' ? round(9/5*$reading+32) : str_replace('.',$dot,$reading)) : '##')."&thinsp;$unit";
}

if ($cpu || $mb || $fan){
	$readings = ipmi_get_reading([$cpu, $mb, $fan], $options);
	$temps = [];

	if ($readings[$cpu])
		$temps[] = "<img src='/plugins/$plugin/icons/cpu.png' title='$cpu' class='icon'>".ipmi_temp($readings[$cpu], $_GET['unit'], $_GET['dot']);

	if ($readings[$mb])
		$temps[] = "<img src='/plugins/$plugin/icons/mb.png' title='$mb' class='icon'>".ipmi_temp($readings[$mb], $_GET['unit'], $_GET['dot']);

	if ($readings[$fan])
		$temps[] = "<img src='/plugins/$plugin/icons/fan.png' title='$fan' class='icon'>".$readings[$fan]."&thinsp;rpm";
}
if ($temps)
	echo "<span id='temps' style='margin-right:16px'>".implode('&nbsp;', $temps)."</span>";
?>