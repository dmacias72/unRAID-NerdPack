<?php
require_once '/usr/local/emhttp/plugins/NerdPack/include/NerdPackHelpers.php';

$pkgs_array = [];

foreach ($pkgs_github_array as $pkg_github) {
	$pkg_nameArray = explode('-', $pkg_github['name']); // split package name into array

	$pkg_name = $pkg_nameArray[0];
	if (sizeof($pkg_nameArray) > 4) { //if package name has a subset get it
		for ($ii = 1; $ii < sizeof($pkg_nameArray)-3; $ii++) {
			$pkg_name .= '-'.$pkg_nameArray[$ii];
		}
	}

	$pkg_version = $pkg_nameArray[sizeof($pkg_nameArray) - 3]; // get package version

	$pkg_nver = $pkg_name.'-'.str_replace('.', '_', $pkg_version); // add underscored version to package name

	$pkg_pattern = '/^'.$pkg_name.'.*/'; // search patter for packages

	$pkg = [
		'name' => $pkg_github['name'], // add full package name
		'pkgname' => $pkg_name, // add package name only
		'pkgnver' => $pkg_nver, // add package name with underscored version
		'pkgversion' => $pkg_version, // add package name with raw version
		'size' => format_size($pkg_github['size'], 1, '?'), // add package size
		'installed' => preg_grep($pkg_pattern, $pkgs_installed) ? 'yes' : 'no', // checks if package name is installed
		'installeq' => in_array(pathinfo($pkg_github['name'], PATHINFO_FILENAME), $pkgs_installed) ? 'yes' : 'no', // checks if package is installed equals github exactly
		'downloaded' => preg_grep($pkg_pattern, $pkgs_downloaded) ? 'yes' : 'no', // checks if package name is downloaded
		'downloadeq' => in_array($pkg_github['name'], $pkgs_downloaded) ? 'yes' : 'no', // checks if package is downloaded equals github exactly
		'config' => isset($pkg_cfg[$pkg_nver]) ? $pkg_cfg[$pkg_nver] : 'no', // checks config for install preference
		'desc' => $pkgs_desc_array[$pkg_name]
	];

	$pkgs_array[] = $pkg;
}

echo json_encode($pkgs_array);
?>