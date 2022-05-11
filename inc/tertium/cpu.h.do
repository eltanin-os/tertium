#!/bin/rc -e
# HDR order is important don't mess with it
HDR=(macros.h.in ctypes.h.in types.h.in prototypes.h.in)
DEPS=($HDR syscalls.in)
ARCH=$MAINDIR/sys/$"OSNAME/$"OBJTYPE
GEN=$MAINDIR/sys/$"OSNAME/generic
redo-ifchange $GEN/$DEPS $ARCH/$DEPS
for (i in $HDR) {
	cat $GEN/$i $ARCH/$i
	echo
}
fn prototypes {
	awk '/^[A-z].*\(.*\)/ { out=$2" c_sys_"$3$4 ; for (i=5; i<=NF;i++) { out=out" "$i }; print out";" }' < $1 | sed -e 's;\([A-z]*\)\* ;\1 *;g' -e 's; {\;$;\;;' -e 's;();(void);' -e 's;\([^,]\) [A-z]*\([,)]\);\1\2;g'
}
prototypes $GEN/syscalls.in
prototypes $ARCH/syscalls.in
