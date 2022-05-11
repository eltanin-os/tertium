#!/bin/rc -e
redo-ifchange $HDR $2
$CC $CFLAGS $CPPFLAGS -I$MAINDIR/inc -o $3 -c $2
