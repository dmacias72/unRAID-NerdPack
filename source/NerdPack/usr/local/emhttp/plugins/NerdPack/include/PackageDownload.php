<?php
include("/usr/local/emhttp/plugins/NerdPack/include/DownloadHelpers.php");
$pkg_path="/boot/config/plugins/NerdPack/packages/";
$pkg_git = "https://raw.githubusercontent.com/eschultz/unraid6-nerdpack/master/packages/";
$pkg_config = "/boot/config/plugins/NerdPack/NerdPack.cfg";
$pkg_cfg = parse_ini_file($pkg_config); // get package configs
//$pkg_pref = $pkg_cfg[$_POST["pkgname"]]; // get package preference
$pkgs_file = file_get_contents("/boot/config/plugins/NerdPack/packages.json"); 
$pkgs_github = json_decode($pkgs_file, true);
for ($i = 0; $i < sizeof($pkgs_github); $i++) {
//	echo $pkgs_github[$i]["name"];
//	echo $pkgs_github[$i]["download_url"];
}

$pkg_file = "/usr/local/emhttp/plugins/NerdPack/include/python-2.7.9-x86_64-1.txz";
$pkg_url = "https://raw.githubusercontent.com/eschultz/unraid6-nerdpack/master/packages/python-2.7.9-x86_64-1.txz";
urlConnect($pkg_file, $pkg_url);


/*$pkg_msg = "$pkg_name package download failed.";
if (file_put_contents($pkg_new, fopen($pkg_git.$pkg_name, 'r')));{
	$pkg_size = filesize($pkg_new);
	$pkg_handle = fopen($pkg_new, "rb");
	$pkg_contents = fread($pkg_handle, $pkg_size);
	fclose($pkg_handle);
	//shell_exec("cd $pkg_path && wget -q $pkg_new");
	$pkg_str = "blob ".$pkg_size."\0".$pkg_contents;
	$pkg_sha = sha1($pkg_str);
	if($pkg_sha == $_POST["pkgsha"]) {
		$pkg_msg = "$pkg_name package downloaded.";
		if (is_file($pkg_old))
			unlink($pkg_old);
		if($pkg_pref == "yes") {
			$pkg_cmd = "upgradepkg --install-new ";
			$pkg_cmd = $pkg_cmd.$pkg_new." | logger -tnerdpack";
			shell_exec($pkg_cmd);
			$pkg_msg = "$pkg_name package updated.";
		}
	}else {
		if (is_file($pkg_new))
			unlink($pkg_new);
	}
}
echo json_encode($pkg_msg);
*/
?>
