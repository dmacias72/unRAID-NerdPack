<?php
/* ipmi tool variables*/
$plugin = 'ipmitool-plugin';
$ipmitool_cfg = parse_ini_file("/boot/config/plugins/$plugin/$plugin.cfg");
$ipmitool_service = isset($ipmitool_cfg['SERVICE']) ? $ipmitool_cfg['SERVICE'] 	: "disable";
$ipmitool_remote = isset($ipmitool_cfg['REMOTE']) ? $ipmitool_cfg['REMOTE'] 	: "disable";
$ipmitool_running = trim(shell_exec( "[ -f /proc/`cat /var/run/ipmievd.pid0 2> /dev/null`/exe ] && echo 'yes' || echo 'no' 2> /dev/null" ));

// get ip address of local ipmi
$ipmitool_lanip = trim(shell_exec("/usr/bin/ipmitool lan print | grep 'IP Address  ' | sed -n -e 's/^.*: //p'"));

// use save ip address or use local ipmi address
$ipmitool_ipaddr = preg_match('/^(?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)(?:[.](?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)){3}$/', $ipmitool_cfg['IPADDR']) ? $ipmitool_cfg['IPADDR'] : $ipmitool_lanip;

$ipmitool_cpu = isset($ipmitool_cfg['CPU_TEMP']) ? $ipmitool_cfg['CPU_TEMP'] : ""; // cpu temp display name
$ipmitool_mb = isset($ipmitool_cfg['MB_TEMP']) ? $ipmitool_cfg['MB_TEMP'] : ""; // mb temp display name
$ipmitool_fan = isset($ipmitool_cfg['IPMI_FAN']) ? $ipmitool_cfg['IPMI_FAN'] : ""; // fan speed display name
$ipmitool_user = isset($ipmitool_cfg['USER']) ? $ipmitool_cfg['USER'] : ""; // user for remote access
$ipmitool_password = isset($ipmitool_cfg['PASSWORD']) ? $ipmitool_cfg['PASSWORD'] : ""; // password for remote access

// options for remote access or not
$ipmitool_options = ($remote == "enable") ? " -I lanplus -H '$ipmitool_ipaddr' -U '$ipmitool_user' -P '".
	base64_decode($ipmitool_password)."' " : "";

/* get an array of all sensors and their values */
function ipmi_sensors($options) {
	$cmd = "/usr/bin/ipmitool -vc sdr $options 2>/dev/null";
	exec($cmd, $output);

	// key names for ipmitool sensor output
	$sensor_keys = array('Name','Reading','Units','Status','Entity','Location','Type','Nominal',
	 'NormalMin','NormalMax','UpperNonRec','UpperCritical','UpperNonCritical','LowerNonRec',
	 'LowerCritical','LowerNonCritical','MinRange','MaxRange' );

	$sensors_array = [];
 
	foreach($output as $sensor){

		// add sensor keys as keys to ipmitool output
		$sensor_array = array_combine($sensor_keys, array_slice(explode(",", $sensor),0,18,true));

		// add sensor to array of sensors
		$sensors_array[] = $sensor_array;	
	}
	return $sensors_array;
}

/* get array of events and their values */
function ipmi_events($options){
	$cmd = "/usr/bin/ipmitool -c sel elist $options 2>/dev/null";
	exec($cmd, $output); 

	// key names for ipmitool event output
	$event_keys = array('Event','Datestamp','Timestamp','Sensor','Description','Status');

	$events_array = [];

	foreach($output as $event){

		// add event keys as keys to ipmitool output cut to match
		$event_array = array_combine($event_keys, array_slice(explode(",", $event),0,6,true));

		$events_array[] = $event_array;
	}
	return $events_array;
}

/* get select options for a given sensor type */
function ipmi_get_options($selected, $type, $options){
	$sensors_array = ipmi_sensors($options);
	$options = "<option value='false'>No</option>\n";
	foreach($sensors_array as $sensor){
		if ($sensor["Type"] == $type && $sensor["Status"] != "ns"){
			$name = $sensor["Name"];
			$options .= "<option value='$name'";

			// set saved option as selected
			if ($selected == $name)
				$options .= " selected";

		$options .= ">$name</option>\n";
		}
	}
	return $options;
}

/* get reading for a given sensor by name */
function ipmi_get_reading($sensor, $options) {

	$sensors_array = ipmi_sensors($options);

	foreach($sensors_array as $sensor_array){
		if ($sensor_array["Name"] == $sensor) {
			return $sensor_array["Reading"];
		}	
	}
}
?>
