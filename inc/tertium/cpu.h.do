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
# HDR order is important don't mess with it
multisubstitute {
define -s HDR "macros.h.in ctypes.h.in types.h.in prototypes.h.in"
define -s DEPS "macros.h.in ctypes.h.in types.h.in prototypes.h.in syscalls.in"
define ARCH "../../sys/${OSNAME}/${OBJTYPE}"
define GEN  "../../sys/${OSNAME}/generic"
}
if { redo-ifchange cpu.h.awk ${GEN}/${DEPS} ${ARCH}/${DEPS} }
redirfd -w 1 $3
if { forx -E header { $HDR } cat ${GEN}/${header} ${ARCH}/${header} }
pipeline { cat ${GEN}/syscalls.in ${ARCH}/syscalls.in } awk -f cpu.h.awk
