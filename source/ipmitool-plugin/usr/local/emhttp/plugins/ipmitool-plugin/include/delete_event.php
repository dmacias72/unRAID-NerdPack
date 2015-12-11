<?php
$command = "/usr/bin/ipmitool sel ".$_POST["options"];
exec($command);
?>
