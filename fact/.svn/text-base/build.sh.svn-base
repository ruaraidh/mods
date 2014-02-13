#!/bin/sh
\rm -f *.o
CC -g -Bdynamic -G -c *cpp -I$SOURCEDIR/base -I$SOURCEDIR/mods/geom -I$SOURCEDIR/mods/test -I$SOURCEDIR/auxl  -c *.cpp
CC -g -Bdynamic -G -o $MODSDIR/lib/libfact.so *.o
\rm -f *.o
