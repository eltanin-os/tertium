#!/bin/execlineb -S3
multisubstitute {
	importas -i OSNAME OSNAME
	importas -i OBJTYPE OBJTYPE
	importas -sD "ar" AR AR
	importas -sD "ranlib" RANLIB RANLIB
}
foreground { redo-ifchange ../src/sys }
multisubstitute {
	elglob -s CO "../src/*/*.c"
	elglob -s SO "../sys/${OSNAME}/${OBJTYPE}/*.s"
}
foreground { redo-ifchange ${CO}.o ${SO}.o }
foreground { $AR rc $3 ${CO}.o ${SO}.o }
$RANLIB $3
