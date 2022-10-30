#!/bin/execlineb -S3
backtick HOSTOS { pipeline -w { tr "[A-Z]" "[a-z]" } uname -s }
backtick HOSTARCH { uname -m }
multisubstitute {
	importas -iu HOSTOS HOSTOS
	importas -iu HOSTARCH HOSTARCH
	importas -D "/usr/local" DESTDIR DESTDIR
	importas -D "/include" INCDIR INCDIR
	importas -D "/lib" LIBDIR LIBDIR
	importas -D "/share/man" MANDIR MANDIR
	define -s HDR "inc/tertium/cpu.h inc/tertium/dat.h inc/tertium/fns.h inc/tertium/std.h"
	elglob MANPAGES "man/*"
}
backtick OSNAME { importas -D "${HOSTOS}" OSNAME OSNAME echo $OSNAME }
backtick OBJTYPE { importas -D "${HOSTARCH}" OBJTYPE OBJTYPE echo $OBJTYPE }
backtick HDR { echo $HDR }
case -- $1 {
".*\.[1ch]" {
	exit 0
}
"all" {
	redo-ifchange lib/libtertium.a
}
"clean" {
	backtick targets { redo-targets }
	importas -isu targets targets
	rm -Rf $targets
}
"install" {
	if { redo-ifchange all }
	if { install -dm 755 "${DESTDIR}${INCDIR}/tertium" }
	if { install -dm 755 "${DESTDIR}${LIBDIR}" }
	if { install -dm 755 "${DESTDIR}${MANDIR}/man3" }
	if { install -cm 644 $MANPAGES "${DESTDIR}/${MANDIR}/man3" }
	if { install -cm 644 $HDR "${DESTDIR}${INCDIR}/tertium" }
	install -cm 644 lib/libtertium.a "${DESTDIR}${LIBDIR}"
}
}
foreground {
	fdmove 1 2
	echo no rule for $1
}
exit 1
