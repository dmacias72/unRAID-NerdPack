## README for nmon

- http://nmon.sourceforge.net/pmwiki.php?n=Site.CompilingNmon has the .c source files. It ALSO has a makefile that includes ARM and X86 and X86_64 compilation flag options.
 - Ncurses needs to be installed. I'm using Slackware-current, which has `ncurses-6.2_20201024-x86_64-1.txz`. It also calls for GCC, so I have `gcc-10.2.0-x86_64-2.txz` installed. Finally, I have `make-4.2.1-x86_64-7.txz` installed, though I guess if I'm calling GCC directly, it's perhaps not necessary
- https://slackbuilds.org/repository/14.2/system/nmon/ has a SlackBuild file, but was made for version 14i which is at least older than April 2015 (nmon15c was released). 
 - The GCC flags are a little out of date in comparison to the makefile, so I copied/merged the flags over. (The changelog notes the deprecation of some of these flags, such as -D LARGEMEM and JFS and GETUSER).
 - NOTE: I did this on an X86_64 system and did not update the compile flags in the SlackBuild for other architectures.  
 - The SlackBuild also has scatterings of hardcoded version numbers, which I updated to be generic `lmon.c` as it is in the makefile. 
 - I also increased the set flags for more verbose output. 
 - Finally, the output was changed from `tgz` to `txz`
- There was a "bug" in the 16m release of nmon where the version number string wasn't bumped from "16k" to "16m". I changed that string so the nmon executable properly shows that it is version 16m. 
- I copied the compiled `nmon-16m-x86_64-1_SBo.txz` file to Unraid 6.8.3 and 6.9-rc1 systems and confirmed that after `installpkg nmon-16m-x86_64-1_SBo.txz` I was able to call `nmon` and start up the utility without issue
 - I thought Ncurses might need to be installed on Unraid for this to work, but it seems to only be needed at compile time.
