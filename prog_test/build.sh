#!/bin/sh
CC -g -Bdynamic -R$MODSDIR/lib -L$MODSDIR/lib -I$SOURCEDIR/base \
      -I$SOURCEDIR/mods/test -I$SOURCEDIR/fact \
       *.cpp $SOURCEDIR/fortran/*.o \
       -o $MODSDIR/bin/prog_test \
        -lbase  -lmods_geom -lmods_test -lfact -lauxl  -lfsu -lfui -lfai
