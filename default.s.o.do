#!/bin/execlineb -S3
importas -sD "cc" CC CC
if { redo-ifchange ${2}.s }
$CC -o $3 -c ${2}.s
