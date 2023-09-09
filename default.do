#!/bin/execlineb -S3
multisubstitute {
	importas -D "" DESTDIR DESTDIR
	importas -D "/usr/local" PREFIX PREFIX
	importas -D "/include" INCDIR INCDIR
	importas -D "/lib" LIBDIR LIBDIR
	importas -D "/share/man" MANDIR MANDIR
	define -s HDR "inc/tertium/cpu.h inc/tertium/dat.h inc/tertium/fns.h inc/tertium/std.h"
	elglob MANPAGES "man/*"
}
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
		if { install -dm 755 "${DESTDIR}${PREFIX}${INCDIR}/tertium" }
		if { install -dm 755 "${DESTDIR}${PREFIX}${LIBDIR}" }
		if { install -dm 755 "${DESTDIR}${PREFIX}${MANDIR}/man3" }
		if { install -cm 644 $MANPAGES "${DESTDIR}${PREFIX}/${MANDIR}/man3" }
		if { install -cm 644 $HDR "${DESTDIR}${PREFIX}${INCDIR}/tertium" }
		install -cm 644 lib/libtertium.a "${DESTDIR}${PREFIX}${LIBDIR}"
	}
}
foreground {
	fdmove 1 2
	echo no rule for $1
}
exit 1
