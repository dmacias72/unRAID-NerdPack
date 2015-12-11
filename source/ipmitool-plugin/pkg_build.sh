#!/bin/bash
DIR="$(dirname "$(readlink -f ${BASH_SOURCE[0]})")"
tmpdir=/tmp/tmp.$(( $RANDOM * 19318203981230 + 40 ))
plugin=$(basename ${DIR})
archive="$(dirname $(dirname ${DIR}))/archive"
version=$(date +"%Y.%m.%d")
package="${archive}/${plugin}-${version}-x86_64-1.txz"
md5="${archive}/${plugin}-${version}-x86_64-1.md5"

if [[ -f $package ]]; then
  for x in a b c d e d f g h ; do
    package="${archive}/${plugin}-${version}${x}-x86_64-1.txz"
    md5="${archive}/${plugin}-${version}${x}-x86_64-1.md5"
    if [[ ! -f $package ]]; then
      break
    fi
  done
fi

mkdir -p $tmpdir
cd "$DIR"
cp --parents -f $(find . -type f ! \( -iname "pkg_build.sh" -o -iname "sftp-config.json" -o -iname ".DS_Store"  \) ) $tmpdir/
cd "$tmpdir/"
makepkg -l y -c y "${package}"
cd "$archive/"
md5sum $(basename "$package") > "$md5"
rm -rf "$tmpdir"

# Verify and install plugin package
sum1=$(md5sum "${package}")
sum2=$(cat "$md5")
if [ "${sum1:0:32}" != "${sum2:0:32}" ]; then
  echo "Checksum mismatched.";
  rm "$md5" "${package}"
else
  echo "Checksum matched."
fi