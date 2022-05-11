#!/bin/rc -e
redo-ifchange $2.s
$CC -o $3 -c $2.s
