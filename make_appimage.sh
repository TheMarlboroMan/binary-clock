#!/bin/bash

if [[ $# -ne 2 ]]
then
	echo "usage: make_appimage.sh path_to_executable path_to_linuxdeploy"
	exit 1
fi;

#export SIGN=1
#export SIGN_KEY=0xLAST8CHARSOFGPGKEYID
MAJOR_VERSION=0
MINOR_VERSION=0
PATCH_VERSION=1

export VERSION="$MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION"
echo "will build $VERSION"
$2 --appdir AppDir
cp -r resources/* AppDir/usr/share
mkdir -p AppDir/usr/share/metainfo
cp linuxdeploy/*.xml AppDir/usr/share/metainfo/
$2 --executable $1 --appdir AppDir -i ./linuxdeploy/binary-clock.png -d ./linuxdeploy/binary-clock.desktop --output appimage
rm -rf AppDir
exit 0
