#!/bin/execlineb -S3
multisubstitute {
	importas -sD "cc" CC CC
	importas -isu HDR HDR
	importas -sD "-O0 -g -std=c99 -Wall -Wextra -pedantic" CFLAGS CFLAGS
	importas -sD "" CPPFLAGS CPPFLAGS
}
if { redo-ifchange ../../${HDR} $2 }
$CC $CFLAGS $CPPFLAGS -I../../inc -o $3 -c $2
