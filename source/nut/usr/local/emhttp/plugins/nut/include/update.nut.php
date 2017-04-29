<?PHP
/* Copyright 2015, Dan Landon.
 * Copyright 2015, Bergware International.
 * Copyright 2015, Lime Technology
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2,
 * as published by the Free Software Foundation.
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Edited by macester for NUT Plugin.
 */
?>
<?
$cfg  = "/boot/config/plugins/nut/nut.cfg";
$connection = $_POST['DRIVER']=='custom' ? $_POST['SERIAL'] : $_POST['DRIVER'];

exec("/etc/rc.d/rc.nut stop");
exec("sed -i -e '/^SERVICE/c\\SERVICE=\"'{$_POST['SERVICE']}'\"' $cfg");
exec("sed -i -e '/^PORT/c\\PORT=\"'{$_POST['PORT']}'\"' $cfg");
exec("sed -i -e '/^MODE/c\\MODE=\"'{$_POST['MODE']}'\"' $cfg");
exec("sed -i -e '/^SHUTDOWN/c\\SHUTDOWN=\"'{$_POST['SHUTDOWN']}'\"' $cfg");
exec("sed -i -e '/^BATTERYLEVEL/c\\BATTERYLEVEL=\"'{$_POST['BATTERYLEVEL']}'\"' $cfg");
exec("sed -i -e '/^SECONDS/c\\SECONDS=\"'{$_POST['SECONDS']}'\"' $cfg");
exec("sed -i -e '/^TIMEOUT/c\\TIMEOUT=\"'{$_POST['TIMEOUT']}'\"' $cfg");
exec("sed -i -e '/^UPSKILL/c\\UPSKILL=\"'{$_POST['UPSKILL']}'\"' $cfg");
exec("sed -i -e '/^DRIVER/c\\DRIVER=\"'{$connection}'\"' $cfg");

if ($_POST['SERVICE']=='enable') exec("/usr/local/emhttp/plugins/nut/scripts/rc.nut start");
?>
