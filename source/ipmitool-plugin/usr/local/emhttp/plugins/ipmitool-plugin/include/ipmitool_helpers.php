<?php
/* ipmi tool variables*/
$plugin = 'ipmitool-plugin';
$cfg 		= parse_ini_file("/boot/config/plugins/$plugin/$plugin.cfg");
$ipmievd = isset($cfg['IPMIEVD']) ? $cfg['IPMIEVD'] 	: "disable";
$ipmifan = isset($cfg['IPMIFAN']) ? $cfg['IPMIFAN'] 	: "disable";
$remote  = isset($cfg['REMOTE'])  ? $cfg['REMOTE']  	: "disable";

//check running status
$ipmievd_running = trim(shell_exec( "[ -f /proc/`cat /var/run/ipmievd.pid0 2> /dev/null`/exe ] && echo 1 || echo 0 2> /dev/null" ));
$ipmifan_running = trim(shell_exec( "[ -f /proc/`cat /var/run/ipmifan.pid 2> /dev/null`/exe ] && echo 1 || echo 0 2> /dev/null" ));
$running = "<span class='green'>Running</span>";
$stopped = "<span class='orange'>Stopped</span>";
$ipmievd_status = ($ipmievd_running) ? $running : $stopped;
$ipmifan_status = ($ipmifan_running) ? $running : $stopped;

// use save ip address or use local ipmi address
$ipaddr = preg_match('/^(?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)(?:[.](?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)){3}$/', $cfg['IPADDR']) ? 
	$cfg['IPADDR'] : 
	trim(shell_exec("/usr/bin/ipmitool lan print | grep 'IP Address  ' | sed -n -e 's/^.*: //p'"));

$cpu      = isset($cfg['CPU_TEMP']) ? $cfg['CPU_TEMP'] : ""; // cpu temp display name
$mb       = isset($cfg['MB_TEMP'])  ? $cfg['MB_TEMP']  : ""; // mb temp display name
$fan      = isset($cfg['IPMI_FAN']) ? $cfg['IPMI_FAN'] : ""; // fan speed display name
$user     = isset($cfg['USER'])     ? $cfg['USER']     : ""; // user for remote access
$password = isset($cfg['PASSWORD']) ? $cfg['PASSWORD'] : ""; // password for remote access

// options for remote access or not
$options = ($remote == "enable") ? "-I lanplus -H '$ipaddr' -U '$user' -P '".
	base64_decode($password)."'" : "";

// Get sensor info and check connection if remote enabled
$sensors = ipmi_sensors($options);
$fans = ipmi_get_fans($sensors);

if($remote == "enable"){
	$conn = ($sensors) ? true : false;
	$conn_check = ($conn) ? "Connection successful" : "Connection failed";
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
		$sensor = array_combine($keys, array_slice(explode(",", $line),0,18,true));

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
function ipmi_get_options($sensors, $type, $selected=null){
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
?>
