## Package Description

LLFUSE is a set of Python bindings for the low level FUSE API. It requires at
least FUSE 2.8.0 and supports both Python 2.x and 3.x.

LLFUSE was originally part of S3QL, but has been factored out so that it can
be used by other projects as well.

The SlackBuild detects presence of Python 3.x and if found,
then also bindings for Python 3.x are built.

Python-LLFUSE is no longer actively maintained. Unless you are stuck with Python 2.x or libfuse 2.x, we recommended to use the pyfuse3 module instead: https://github.com/libfuse/pyfuse3

## kubedzero notes

* I set up Slackware-current (15.0) based on a Princeton ISO http://mirror.math.princeton.edu/pub/slackware/slackware-iso/slackware-current-iso/ and then updated all the packages.
* I made sure `fuse-2.9.9` and `fuse3-3.10.0` were installed, along with `python`, `python3`, `pip`, and `setuptools`
* I copied over `slack-desc` and `llfuse.SlackBuild` from this repository, making sure the SlackBuild is executable. The other files don't seem to be used.
* I then downloaded the latest ZIP source of llfuse from https://github.com/python-llfuse/python-llfuse/archive/release-1.3.8.zip and put it in the same directory as the SlackBuild script.
* Finally, I executed the SlackBuild script. It unzips the Github source archive to a directory created in `/tmp/` and runs `setup.py build_cython` as well as `setup.py install` with both Python 2 and Python 3. It also copies some other files over, and then packages the compiled files into a Slack-installable `/tmp/llfuse-1.3.8-x86_64-1_SBo.txz` file
* NOTE: The SlackBuild script will need to be updated with a new version number to build future versions of this library
* NOTE: https://github.com/python-llfuse/python-llfuse/blob/master/developer-notes/release-process.md had some additional setup and development notes
* NOTE: If you see `gcc: error: src/llfuse.c: No such file or directory` after `gcc -pthread -fno-strict-aliasing -g -O2 -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-pro -o build/temp.linux-x86_64-2.7/src/llfuse.o -D_FILE_OFFSET_BITS=64 -I/usr/include/-Wsign-compare -DLLFUSE_VERSION="1.3.7" -Wno-unused-function -Wno-implicit-fallthroerror=unreachable-code -Werror=conversion -Werror=sign-compare -fno-strict-aliasing` it's possible that `setup.py build_cython` did not run to completion and thus did not create the compiled `.c` files

 ## Package versions

 These are the package versions installed during the 2020/11 build of llfuse:

 ```
 Package        Version
-------------- ---------
-lxc           0.1
appdirs        1.4.4
Brotli         1.0.9
caca           0.99b19
certifi        2020.11.8
chardet        3.0.4
cupshelpers    1.0
Cython         0.29.21
distro         1.5.0
docutils       0.16
future         0.18.2
getmail6       6.9
gpg            1.14.0
gyp            0.1
idna           2.10
include-server 3.3.3
isc            2.0
libwebp        0.0
M2Crypto       0.36.0
Mako           1.1.3
mercurial      5.6
meson          0.56.0
netsnmp-python 1.0a1
notify2        0.3.1
packaging      20.4
Pillow         8.0.1
pip            20.2.4
ply            3.11
pssh           2.3.4
pwquality      1.4.4
pycairo        1.20.0
pycups         2.0.1
pycurl         7.43.0.6
Pygments       2.7.2
PyGObject      3.36.1
pyparsing      2.4.7
PyQt4-sip      4.19.23
PyQt5          5.15.1
PyQt5-sip      12.8.1
python-sane    2.8.3
pyxdg          0.27
QScintilla     2.11.5
requests       2.25.0
rpm            4.16.0
SCons          4.0.1
setuptools     50.3.2
sip            5.4.0
six            1.15.0
toml           0.10.2
undervolt      0.3.0
urllib3        1.26.2
```

```
root@slack:~# slackpkg search <packageName>

[ installed ] - fuse-2.9.9-x86_64-1
[ installed ] - fuse3-3.10.0-x86_64-1
[ installed ] - python-pip-20.2.4-x86_64-2
[ installed ] - python-setuptools-50.3.2-x86_64-2
[ installed ] - python2-2.7.18-x86_64-2
[ installed ] - python3-3.9.0-x86_64-1
```