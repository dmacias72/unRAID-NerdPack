<?php
/* ipmi tool variables*/
$plugin = 'ipmitool-plugin';
$ipmi_cfg 		= parse_ini_file("/boot/config/plugins/$plugin/$plugin.cfg");
$ipmievd = isset($ipmi_cfg['IPMIEVD']) ? $ipmi_cfg['IPMIEVD'] 	: "disable";
$ipmifan = isset($ipmi_cfg['IPMIFAN']) ? $ipmi_cfg['IPMIFAN'] 	: "disable";
$ipmi_remote  = isset($ipmi_cfg['REMOTE'])  ? $ipmi_cfg['REMOTE']  	: "disable";

//check running status
$ipmievd_running = trim(shell_exec( "[ -f /proc/`cat /var/run/ipmievd.pid0 2> /dev/null`/exe ] && echo 1 || echo 0 2> /dev/null" ));
$ipmifan_running = trim(shell_exec( "[ -f /proc/`cat /var/run/ipmifan.pid 2> /dev/null`/exe ] && echo 1 || echo 0 2> /dev/null" ));
$ipmi_running = "<span class='green'>Running</span>";
$ipmi_stopped = "<span class='orange'>Stopped</span>";
$ipmievd_status = ($ipmievd_running) ? $ipmi_running : $ipmi_stopped;
$ipmifan_status = ($ipmifan_running) ? $ipmi_running : $ipmi_stopped;

// use save ip address or use local ipmi address
$ipmi_ipaddr = preg_match('/^(?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)(?:[.](?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)){3}$/', $ipmi_cfg['IPADDR']) ? 
	$ipmi_cfg['IPADDR'] : 
	trim(shell_exec("/usr/bin/ipmitool lan print | grep 'IP Address  ' | sed -n -e 's/^.*: //p'"));

$ipmi_cpu_temp = isset($ipmi_cfg['CPU_TEMP']) ? $ipmi_cfg['CPU_TEMP'] : ""; // cpu temp display name
$ipmi_mb_temp  = isset($ipmi_cfg['MB_TEMP'])  ? $ipmi_cfg['MB_TEMP']  : ""; // mb temp display name
$ipmi_fan_disp = isset($ipmi_cfg['FAN_DISP']) ? $ipmi_cfg['FAN_DISP'] : ""; // fan speed display name
$ipmi_user     = isset($ipmi_cfg['USER'])     ? $ipmi_cfg['USER']     : ""; // user for remote access
$ipmi_password = isset($ipmi_cfg['PASSWORD']) ? $ipmi_cfg['PASSWORD'] : ""; // password for remote access

// options for remote access or not
$ipmi_options = ($ipmi_remote == "enable") ? "-I lanplus -H '$ipmi_ipaddr' -U '$ipmi_user' -P '".
	base64_decode($ipmi_password)."'" : "";

// Get sensor info and check connection if remote enabled
$ipmi_sensors = ipmi_sensors($ipmi_options);
$ipmi_fans = ipmi_get_fans($ipmi_sensors);

if($ipmi_remote == "enable"){
	$ipmi_conn = ($ipmi_sensors) ? true : false;
	$ipmi_conn_check = ($ipmi_conn) ? "Connection successful" : "Connection failed";
}

/* get an array of all sensors and their values */
function ipmi_sensors($options) {
	$cmd = "/usr/bin/ipmitool -vc sdr $options -N 1 -R 1 2>/dev/null"; // N seconds R retries
	exec($cmd, $output, $return);

	if ($return)
		return []; // return empty array if error

	// key names for ipmitool sensor output
	$keys = ['Name','Reading','Units','Status','Entity','Location','Type','Nominal',
	 'NormalMin','NormalMax','UpperNonRec','UpperCritical','UpperNonCrit','LowerNonRec',
	 'LowerCritical','LowerNonCrit','MinRange','MaxRange'];

	$sensors = [];

	foreach($output as $line){

		// add sensor keys as keys to ipmitool output
		$sensor_raw = explode(",", $line);
		$size_raw = sizeof($sensor_raw);
		$sensor = ($size_raw < 18) ? []:
		  /*array_combine(array_slice($keys,0,$size_raw,true), $sensor_raw)*/
			 array_combine($keys, array_slice($sensor_raw,0,18,true));

		// add sensor to array of sensors
		$sensors[] = $sensor;
	}
	return $sensors;
}

/* get array of events and their values */
function ipmi_events($options=null){
	$cmd = "/usr/bin/ipmitool -c sel elist $options -N 1 -R 1 2>/dev/null"; // N seconds R retries
	exec($cmd, $output, $return); 

	if ($return)
		return []; // return empty array if error

	// key names for ipmitool event output
	$keys = array('Event','Datestamp','Timestamp','Sensor','Description','Status');

	$events = [];

	foreach($output as $line){

		// add event keys as keys to ipmitool output cut to match
		$event = array_combine($keys, array_slice(explode(",", $line),0,6,true));

		$events[] = $event;
	}
	return $events;
}

/* get select options for a given sensor type */
function ipmi_get_options($sensors, $type, $selected=null, $hdd=null){
	if ($hdd)
		$sensors[] = ['Name' => 'HDD Temperature', 'Type' => 'Temperature', 'Status' => 'ok'];
	$options = "";
	foreach($sensors as $sensor){
		if ($sensor["Type"] == $type && $sensor["Status"] != "ns"){
			$name = $sensor["Name"];
			$options .= "<option value='$name'";

			// set saved option as selected
			if ($selected == $name)
				$options .= " selected";

		$options .= ">$name</option>";
		}
	}
	return $options;
}

// get options for high or low temp thresholds
function temp_get_options($range, $selected=null){
	$temps = [20,25,30,35,40,45,50,55,60,65,70,75,80];
	if ($range == 'HIGH')
	  rsort($temps);
 $options = "";
 foreach($temps as $temp){
			$options .= "<option value='$temp'";

			// set saved option as selected
			if ($selected == $temp)
				$options .= " selected";

		$options .= ">$temp</option>";

 	}
 	return $options;
	}

/* get reading for a given sensor by name */
function ipmi_get_reading($names, $options=null) {
	$readings = [];
	$cmd = "/usr/bin/ipmitool -c sdr $options -N 1 -R 1 2>/dev/null"; // N seconds R retries
	exec($cmd, $output, $return);

	if ($return)
		return []; // return empty array if error

	for ($i = 0; $i < sizeof($names); $i++) {

		foreach($output as $line){
			$sensor = explode(",", $line);
		
			if ($sensor[0] == $names[$i]) // check name
				$readings[$names[$i]] = $sensor[1]; // get reading by name from readings
		}
	}
	return $readings; // reading
}

function ipmi_get_fans($sensors){
	foreach($sensors as $sensor){
		if ($sensor['Type'] == 'Fan' && $sensor['Status'] != 'ns')
			$fans[] = str_replace(' ', '_', $sensor['Name']); 
	}
	return $fans;
}
//echo json_encode($ipmi_sensors);
?>