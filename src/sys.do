#!/bin/execlineb -S3
multisubstitute {
	importas -i OSNAME OSNAME
	importas -i OBJTYPE OBJTYPE
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
