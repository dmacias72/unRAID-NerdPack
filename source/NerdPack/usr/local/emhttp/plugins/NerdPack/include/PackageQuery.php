<?php
$config_file = "/boot/config/plugins/NerdPack/NerdPack.cfg";

$pkg_path = "/boot/config/plugins/NerdPack/packages/"; // package path

$pkg_cfg = (is_file($config_file)) ? parse_ini_file($config_file) : array(); // get package configs

$pkgs_downloaded = array_diff( scandir($pkg_path, 1), array(".", "..") ); // get array of packages

$pkgs_installed = array_diff( scandir("/var/log/packages", 1), array(".", "..") ); // get array of all installed packages

$pkgs_file = file_get_contents("/boot/config/plugins/NerdPack/packages.json"); 

$pkgs_github = json_decode($pkgs_file, true);


$pkgs_array = array();

for ($i = 0; $i < sizeof($pkgs_github); $i++) {

	$pkg_nameArray = explode("-", $pkgs_github[$i]["name"]); // split package name into array

	$pkg_name = $pkg_nameArray[0];
  	if (sizeof($pkg_nameArray) > 4){ //if package name has a subset get it
		for ($ii = 1; $ii < sizeof($pkg_nameArray)-3; $ii++) {
			$pkg_name = $pkg_name."-".$pkg_nameArray[$ii];
		} 
	}

	$pkg_version = $pkg_nameArray[sizeof($pkg_nameArray)-3]; // get package version

	$pkg_nver = $pkg_name."-".str_replace(".", "_", $pkg_version); // add underscored version to package name
	
	$pkg_pattern = "/^".$pkg_name.".*/"; // search patter for packages

	$pkg = array();

	$pkg["name"] = $pkgs_github[$i]["name"]; // add full package name

	$pkg["pkgname"] = $pkg_name; // add package name only

	$pkg["pkgnver"] = $pkg_nver; // add package name with underscored version
	
	$pkg["pkgversion"] = $pkg_version; // add package name with underscored version

	$pkg["size"] = $pkgs_github[$i]["size"]; // add package size
	
	// checks if package name is installed
	$pkg["installed"] = preg_grep($pkg_pattern , $pkgs_installed) ? "yes" : "no";

	// checks if package is installed equals github exactly
	$pkg["installeq"] = in_array( pathinfo($pkgs_github[$i]["name"], PATHINFO_FILENAME), $pkgs_installed ) ? "yes" : "no"; 

	// checks if package name is downloaded
	$pkg["downloaded"] = preg_grep($pkg_pattern , $pkgs_downloaded) ? "yes" : "no";

	// checks if package is downloaded equals github exactly
	$pkg["downloadeq"] = in_array( $pkgs_github[$i]["name"], $pkgs_downloaded ) ? "yes" : "no";

	$pkg["config"] = isset($pkg_cfg["$pkg_nver"]) ? $pkg_cfg["$pkg_nver"] : "no"; // checks config for install preference

	$pkgs_array[] = $pkg;
}

echo json_encode($pkgs_array);
?>