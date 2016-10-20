<?
// Download a file from given url
function get_file_from_url($file, $url) {
    $chfile = fopen($file, 'w');
    $ch = curl_init();
    $ch_vers = curl_version();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    //curl_setopt($ch, CURLOPT_TIMEOUT, 3600);
curl_setopt($ch, CURLOPT_NOPROGRESS, true);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_USERAGENT, 'curl/'.$ch_vers['version']);
    //curl_setopt($ch, CURLOPT_PROGRESSFUNCTION, 'progress_bar');
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_FILE, $chfile);
    curl_exec($ch);
    curl_close($ch);
    fclose($chfile);
}

// get a json array of the contents of gihub repo
function get_content_from_github($repo, $file) {
    $ch = curl_init();
    $ch_vers = curl_version();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_TIMEOUT, 30);
    curl_setopt($ch, CURLOPT_HTTPHEADER, ['Accept: application/json', 'Content-Type: application/json']);
    curl_setopt($ch, CURLOPT_USERAGENT, 'curl/'.$ch_vers['version']);
    curl_setopt($ch, CURLOPT_URL, $repo);
    $content = curl_exec($ch);
    curl_close($ch);
    if (!empty($content) && (!is_file($file) || $content != file_get_contents($file)))
        file_put_contents($file, $content);
}

// Compare the github sha1 value of a file
function file_check_sha1($file, $sha1) {
    $size = filesize($file);
    $contents = file_get_contents($file);

    // create a sha1 like github does
    $str = "blob ".$size."\0".$contents;
    $sha1_file = sha1($str);

    return ($sha1_file == $sha1);
}
?>