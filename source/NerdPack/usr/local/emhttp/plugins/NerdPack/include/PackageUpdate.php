<?php
$pkg_path="/boot/config/plugins/NerdPack/packages/";
$pkg_git = "https://raw.githubusercontent.com/eschultz/unraid6-nerdpack/master/packages/";

$pkg_name = $_POST["pkgnew"];
$pkg_new = $pkg_path.$pkg_name;

$pkg_config = "/boot/config/plugins/NerdPack/NerdPack.cfg";
$pkg_cfg = parse_ini_file($pkg_config); // get package configs
$pkg_pref = $pkg_cfg[$_POST["pkgname"]]; // get package preference
$pkg_old = $pkg_path.$_POST["pkgold"];

$pkg_msg = "$pkg_name package download failed.";
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
?>
