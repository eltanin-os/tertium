#!/bin/rc -e
redo-ifchange $HDR $2
$CC $CFLAGS $CPPFLAGS -I../../inc -o $3 -c $2
