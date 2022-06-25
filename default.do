#!/bin/rc -e
if (~ $1 *.[1chs] || ~ $1 *.in || ~ $1 *.rc) exit
MAINDIR=$PWD
if (test -e config.rc) {
	redo-ifchange config.rc
	. $MAINDIR/config.rc ||;
}; if not {
	redo-ifcreate config.rc
}
HDR=$MAINDIR'/inc/tertium/'^(cpu.h dat.h fns.h std.h)
MANPAGES=man/*
switch ($1) {
case all
	redo-ifchange lib/libtertium.a
case clean
	rm -f `{redo-targets}
	rm -Rf src/sys
case install
	redo-always
	redo-ifchange all
	install -dm 755 $"DESTDIR$"INCDIR/tertium
	install -dm 755 $"DESTDIR$"LIBDIR
	install -cm 644 $HDR $"DESTDIR$"INCDIR/tertium
	install -cm 644 lib/libtertium.a $"DESTDIR$"LIBDIR
case install-man
	redo-always
	redo-ifchange $MANPAGES
	install -dm 755 $"DESTDIR/$"MANDIR/man3
	install -cm 644 $MANPAGES $"DESTDIR/$"MANDIR/man3
case *
	echo no rule for ''''$1'''' >[1=2]
	exit 1
}
