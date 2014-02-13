#!/bin/sh
\rm -f *.o
CC -g -Bdynamic -G -c *cpp -I$SOURCEDIR/fact -I$SOURCEDIR/testfact -c *.cpp
CC -g -Bdynamic -G -o $MODSDIR/lib/libbase.so *.o
\rm -f *.o
