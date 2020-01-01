<?
require_once '/usr/local/emhttp/plugins/NerdPack/include/NerdPackHelpers.php';
require_once '/usr/local/emhttp/plugins/NerdPack/include/DownloadHelpers.php';

// Only download repo update if the current one is 1 hour old or more
if (!file_exists($repo_file) || !empty($_GET['force']) || (filemtime($repo_file) < (time() - 3600))) {
    get_content_from_github($pkg_repo, $repo_file);
    get_content_from_github($pkg_desc, $desc_file);
    $pkgs_desc_array   = file_exists($desc_file) ? json_decode(file_get_contents($desc_file), true) : [];
    $pkgs_github_array = file_exists($repo_file) ? json_decode(file_get_contents($repo_file), true) : [];
}

$pkgs_array = [];

foreach ($pkgs_github_array as $pkg_github) {
    $pkg_nameArray = explode('-', $pkg_github['name']); // split package name into array

    // strip md5 files
    if(!strpos(end($pkg_nameArray),'.md5')) {

        $pkg_name = $pkg_nameArray[0];

        if (sizeof($pkg_nameArray) > 4) { //if package name has a subset get it
            for ($ii = 1; $ii < sizeof($pkg_nameArray)-3; $ii++) {
                $pkg_name .= '-'.$pkg_nameArray[$ii];
            }
        }

        $pkg_version = $pkg_nameArray[sizeof($pkg_nameArray) - 3]; // get package version

        $pkg_nver    = $pkg_name.'-'.str_replace('.', '_', $pkg_version); // add underscored version to package name

        $pkg_pattern = '/^'.$pkg_name.'-[0-9].*/'; // search pattern for packages

        // check all plugins for package dependency
        $plugins =  [];
        exec("cd /boot/config/plugins ; find *.plg | xargs grep '${pkg_name}-${pkg_version}' -sl",$plugins);
        $pkg_plgs = '--';
        if ($plugins){
            foreach ($plugins as $plugin){
                $pkg_plgs .= pathinfo($plugin, PATHINFO_FILENAME).', ';
                }
            $pkg_plgs =	substr($pkg_plgs, 2, -2);
        }

        // get package preference from config file
        $pkg_set = "no";
        foreach ($pkg_cfg as $pkg_key => $pkg_line) {
            if (preg_match('/^'.$pkg_name.'.*/',$pkg_key)){
                if(sizeof(array_diff(explode('-', $pkg_key), explode('-', $pkg_name))) < 2 ){
                    $pkg_set = $pkg_line;
                    break;
                }
            }
        }

        $pkg = [
            'name'       => $pkg_github['name'], // add full package name
            'pkgname'    => $pkg_name, // add package name only
            'pkgnver'    => $pkg_nver, // add package name with underscored version
            'pkgversion' => $pkg_version, // add package name with raw version
            'size'       => format_size($pkg_github['size'], 1, '?'), // add package size
            'installed'  => !empty(preg_grep($pkg_pattern, $pkgs_installed)) ? 'yes' : 'no', // checks if package name is installed
            'installeq'  => in_array(pathinfo($pkg_github['name'], PATHINFO_FILENAME), $pkgs_installed) ? 'yes' : 'no', // checks if package installed equals github exactly
            'downloaded' => !empty(preg_grep($pkg_pattern, $pkgs_downloaded)) ? 'yes' : 'no', // checks if package name is downloaded
            'downloadeq' => in_array($pkg_github['name'], $pkgs_downloaded) ? 'yes' : 'no', // checks if package downloaded equals github exactly
            'config'     => $pkg_set, // install preference
            'plugins'    => $pkg_plgs, // plugins dependency on package
            'desc'       => $pkgs_desc_array[$pkg_name]
        ];

        $pkgs_array[] = $pkg;
    }
}

$return = [
        'packages' => $pkgs_array,
        'empty'    => empty($pkgs_downloaded)
    ];

echo json_encode($return);
?>