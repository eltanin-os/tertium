#!/bin/execlineb -S3
define -s HDR "inc/tertium/cpu.h inc/tertium/dat.h inc/tertium/fns.h inc/tertium/std.h"
case -- $1 {
	".*\.[1ch]" {
		exit 0
	}
	"all" {
		backtick HDR { echo $HDR }
		redo-ifchange lib/libtertium.a
	}
	"clean" {
		backtick targets { redo-targets }
		importas -isu targets targets
		rm -Rf $targets
	}
	"install" {
		if { redo-ifchange all }
		multisubstitute {
			importas -D "" DESTDIR DESTDIR
			importas -D "/usr/local" PREFIX PREFIX
		}
		if {
			importas -D "/include" INCDIR INCDIR
			if { install -dm 755 "${DESTDIR}${PREFIX}${INCDIR}/tertium" }
			install -cm 644 $HDR "${DESTDIR}${PREFIX}${INCDIR}/tertium"
		}
		if {
			importas -D "/lib" LIBDIR LIBDIR
			if { install -dm 755 "${DESTDIR}${PREFIX}${LIBDIR}" }
			install -cm 644 lib/libtertium.a "${DESTDIR}${PREFIX}${LIBDIR}"
		}
		importas -D "/share/man" MANDIR MANDIR
		if { install -dm 755 "${DESTDIR}${PREFIX}${MANDIR}/man3" }
		elglob MANPAGES "man/*"
		install -cm 644 $MANPAGES "${DESTDIR}${PREFIX}/${MANDIR}/man3"
	}
}
foreground {
	fdmove 1 2
	echo no rule for $1
}
exit 1
