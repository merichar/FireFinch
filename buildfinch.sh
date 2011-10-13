#!/bin/bash
echo "Removing .xpi and .so files from current working dir"
rm Finch.xpi
rm Finch.so
rm Finch.dylib
echo "Building Finch..."
echo -n "Select build environment (osx, linux): "
read -e DIST
if [ "$DIST" != "osx" -a "$DIST" != "linux" -a -z "$DIST" ] ; then 
	echo "Invalid option: $DIST, Valid options are 'osx' or 'linux'"
	exit 	
fi
make -f Makefile.$DIST
echo "Moving compiled extension to package build dir"
if [ "$DIST" == "osx" ] ; then 
	FILE="Finch.dylib"
else if [ "$DIST" == "linux" ] ; then 
	FILE="Finch.so"
	fi
fi
cp $FILE extension_building/Finch/components/$FILE
cd extension_building/
rm Finch.xpi
cd Finch
echo "Creating xpi file..."
zip -r ../Finch.xpi ./*
cp ../Finch.xpi ../../
cd ../../

