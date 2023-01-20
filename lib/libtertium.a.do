#!/bin/execlineb -S3
backtick HOSTOS { pipeline -w { tr "[A-Z]" "[a-z]" } uname -s }
backtick HOSTARCH { uname -m }
multisubstitute {
	importas -i HOSTOS HOSTOS
	importas -i HOSTARCH HOSTARCH
}
multisubstitute {
	importas -D "${HOSTOS}" OSNAME OSNAME
	importas -D "${HOSTARCH}" OBJTYPE OBJTYPE
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
