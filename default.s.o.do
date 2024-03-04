#!/bin/execlineb -S3
if { redo-ifchange ${2}.s }
importas -sD "cc" CC CC
$CC -o $3 -c ${2}.s
