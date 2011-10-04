#!/bin/bash
echo "Removing .xpi and .so files from current working dir"
rm Finch.xpi
rm Finch.so
echo "Building Finch..."
make
echo "Moving compiled extension to package build dir"
cp Finch.so extension_building/Finch/components/Finch.so
cd extension_building/
rm Finch.xpi
cd Finch
echo "Creating xpi file..."
zip -r ../Finch.xpi ./*
cp ../Finch.xpi ../../
cd ../../

