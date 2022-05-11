#!/bin/rc -e
ARCH=$MAINDIR/sys/$"OSNAME/$"OBJTYPE
GEN=$MAINDIR/sys/$"OSNAME/generic
redo-ifchange $MAINDIR/src/sysgen.rc $GEN/syscalls.in $ARCH/syscalls.in
rm -Rf sys; mkdir sys
$MAINDIR/src/sysgen.rc $GEN/syscalls.in $MAINDIR/src/sys
$MAINDIR/src/sysgen.rc $ARCH/syscalls.in $MAINDIR/src/sys
echo 'DONE.'
