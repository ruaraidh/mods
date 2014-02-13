#!/bin/sh
MODSDIR=/home/rmackenz/src/cpp/mods/
export MODSDIR
SOURCEDIR=/home/rmackenz/src/cpp/mods/src/trunk
export SOURCEDIR
cd $SOURCEDIR
#
cd base
echo 'building base...'
build.sh
cd ../
cd mods
echo 'building mods...'
build.sh
cd ../
cd fact
echo 'building fact...'
build.sh
cd ../
cd prog_geom
echo 'building prog_geom...'
build.sh
cd ../
cd prog_test
echo 'building prog_test...'
build.sh
cd ../
