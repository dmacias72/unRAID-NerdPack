<?php
$filename = "/boot/config/plugins/NerdPack/packages/".$_POST["pkg"];
if (is_file($filename));
	unlink($filename);
?>
