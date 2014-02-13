#!/bin/sh
\rm -f *.o
CC -g -Bdynamic -G -c *cpp
CC -g -Bdynamic -G -o $MODSDIR/lib/libauxl.so *.o
\rm -f *.o

