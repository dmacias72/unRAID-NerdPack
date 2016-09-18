<?php
$plg_path = '/boot/config/plugins/NerdPack/'; // plugin path
$os_version = substr(parse_ini_file('/etc/unraid-version')['version'],0,3);
$pkg_path = $plg_path."packages/$os_version/"; // package path
if (!is_dir($pkg_path))
    mkdir($pkg_path);

$pkg_desc = 'https://raw.githubusercontent.com/dmacias72/unRAID-plugins/master/plugins/packages-desc';
$pkg_repo = "https://api.github.com/repos/dmacias72/unRAID-plugins/contents/packages/$os_version";

$desc_file   = $pkg_path.'packages-desc';
$repo_file   = $pkg_path.'packages.json';
$config_file = $plg_path.'NerdPack.cfg';

// get package configs
$pkg_cfg = file_exists($config_file) ? parse_ini_file($config_file) : [];

// get array of downloaded packages
$pkgs_downloaded   = is_dir($pkg_path) ? array_diff(scandir($pkg_path, 1), ['.', '..','packages.json','packages-desc']) : [];

// get array of all installed packages
$pkgs_installed    = array_diff(scandir("/var/log/packages", 1), ['.', '..']);

$pkgs_desc_array   = file_exists($desc_file) ? json_decode(file_get_contents($desc_file), true) : [];

$pkgs_github_array = file_exists($repo_file) ? json_decode(file_get_contents($repo_file), true) : [];

function logger($output, $quiet = false) {
    exec('echo '.escapeshellarg($output).' 2>&1 | logger -tnerdpack');
    if (!$quiet) {
        echo "\n".$output." \n";
        usleep(100000);
    }
}

function format_size($value, $decimals, $unit = '?') {
    if ($value == '')
        return 'unknown';

    /* Autodetect unit that's appropriate */
    if ($unit == '?') {
        if ($value >= 1099511627776)
            $unit = 'T';
        else
        if ($value >= (1 << 30))
            $unit = 'G';
        else
        if ($value >= (1 << 20))
            $unit = 'M';
        else
        if ($value >= (1 << 10))
            $unit = 'K';
        else
            $unit = 'B';
    }

    $unit = strtoupper($unit);

    switch ($unit) {
        case 'T': return number_format($value / (float)1099511627776, $decimals).' TB';
        case 'G': return number_format($value / (float)(1 << 30), $decimals).' GB';
        case 'M': return number_format($value / (float)(1 << 20), $decimals).' MB';
        case 'K': return number_format($value / (float)(1 << 10), $decimals).' KB';
        case 'B': return $value.' B';
    }

    return false;
}
?>
