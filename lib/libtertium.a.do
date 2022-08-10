#!/bin/execlineb -S3
multisubstitute {
importas -i OSNAME OSNAME
importas -i OBJTYPE OBJTYPE
importas -D "ar" AR AR
importas -D "ranlib" RANLIB RANLIB
}
foreground { redo-ifchange ../src/sys }
multisubstitute {
elglob CO "../src/*/*.c"
elglob SO "../sys/${OSNAME}/${OBJTYPE}/*.s"
}
foreground { redo-ifchange ${CO}".o" ${SO}".o" }
foreground { $AR rc $3 ${CO}".o" ${SO}".o" }
$RANLIB $3
