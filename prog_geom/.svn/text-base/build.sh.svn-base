#!/bin/sh
CC -g -Bdynamic -L$MODSDIR/lib -R$MODSDIR/lib -I$SOURCEDIR/base \
      -I$SOURCEDIR/mods/geom -I$SOURCEDIR/fact \
       *.cpp $SOURCEDIR/fortran/*.o \
       -o $MODSDIR/bin/prog_geom \
        -lbase  -lfact -lmods_geom -lmods_test -lauxl  -lfsu -lfui -lfai

