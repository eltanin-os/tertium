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
}
multisubstitute {
	define ARCH "../sys/${OSNAME}/${OBJTYPE}/syscalls.in"
	define GEN  "../sys/${OSNAME}/generic/syscalls.in"
}
if { redo-ifchange sys.awk $GEN $ARCH }
if { mkdir $3 }
cd $3
if { pipeline { cat ../${GEN} ../${ARCH} } awk -f ../sys.awk }
rm -Rf sys
