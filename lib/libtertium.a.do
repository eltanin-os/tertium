#!/bin/rc -e
redo-ifchange $MAINDIR/src/sysfile
CO=`{find $MAINDIR/src -type f -name '*.c'}^'.o'
SO=`{find $MAINDIR/sys/$OSNAME/$OBJTYPE -name '*.s'}^'.o'
redo-ifchange $CO $SO
rm -f $3 # 'ar' can't update objects with same name correctly
$AR rc $3 $CO $SO
$RANLIB $3
