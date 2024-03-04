#!/bin/execlineb -S3
if {
	importas -isu HDR HDR
	redo-ifchange ../../${HDR} $2
}
multisubstitute {
	importas -sD "cc" CC CC
	importas -sD "-O0 -g -std=c99 -Wall -Wextra -pedantic" CFLAGS CFLAGS
	importas -sD "" CPPFLAGS CPPFLAGS
}
$CC $CFLAGS $CPPFLAGS -I../../inc -o $3 -c $2
