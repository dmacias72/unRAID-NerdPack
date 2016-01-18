<?php
$cmd = "/usr/bin/ipmitool sel ".$_POST["options"];
exec($cmd);
?>
