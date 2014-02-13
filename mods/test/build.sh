#!/bin/sh
\rm -f *.o
CC -g -Bdynamic -G -c *cpp -I$SOURCEDIR/base -I$SOURCEDIR/auxl  -c *.cpp
CC -g -Bdynamic -G -o $MODSDIR/lib/libmods_test.so *.o
\rm -f *.o

