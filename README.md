# unRAID 6.1+
unRAID plugins and packages

These are notes more for my memory or for anyone who wants to make unRAID plugins using this structure

I manage this on my laptop running Linux Mint Mate

I use Sublime Text as an editor and SmarGit to upload to github

copy tar-1.13 from unRAID to /bin/tar-1.13 on laptop

copy makepkg from unRAID to /sbin/makepkg on laptop

I modified gfjardim's pkg_build.sh to take an argument and add arch type plus modified the lettering function

To compile the packages for unRAID plugin run from the source directory

sudo ./mkpkg plugin

This creates a slackware compliant package and md5 in the archive directory with the date as the version number

And adds the date to the plugin file in plugins directory.

e.g. plugin-2017.06.09-x86_64-1.txz and plugin-2016.06.09-x86_64-1.md5

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=BKQJF5NVA5E3S)
