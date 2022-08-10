#!/bin/execlineb -S3
backtick HOSTOS { pipeline -w { tr "[A-Z]" "[a-z]" } uname -s }
backtick HOSTARCH { uname -m }
importas -i PWD PWD
multisubstitute {
	importas -iu HOSTOS HOSTOS
	importas -iu HOSTARCH HOSTARCH
	importas -D "/usr/local" DESTDIR DESTDIR
	importas -D "/include" INCDIR INCDIR
	importas -D "/lib" LIBDIR LIBDIR
	elglob MANPAGES "${PWD}/man/*"
	elglob HDR "${PWD}/inc/tertium/*.h"
}
backtick OSNAME { importas -D "${HOSTOS}" OSNAME OSNAME echo $OSNAME }
backtick OBJTYPE { importas -D "${HOSTARCH}" OBJTYPE OBJTYPE echo $OBJTYPE }
backtick HDR { echo "${PWD}/inc/tertium/cpu.h" $HDR }
ifelse { test "${1}" = "all" } {
	redo-ifchange lib/libtertium.a
}
ifelse { test "${1}" = "clean" } {
	backtick targets { redo-targets }
	importas -su targets targets
	foreground { rm -Rf $targets }
}
ifelse { test "${1}" = "install" } {
	foreground { redo-always }
	foreground { redo-ifchange all }
	foreground { install -dm 755 "${DESTDIR}${INCDIR}/tertium" }
	foreground { install -dm 755 "${DESTDIR}${LIBDIR}" }
	foreground { install -dm 755 "${DESTDIR}${MANDIR}/man3" }
	foreground { install -cm 644 $MANPAGES "${DESTDIR}/${MANDIR}/man3" }
	foreground { install -cm 644 $HDR "${DESTDIR}${INCDIR}/tertium" }
	install -cm 644 lib/libtertium.a "${DESTDIR}${LIBDIR}"
}
exit 0
