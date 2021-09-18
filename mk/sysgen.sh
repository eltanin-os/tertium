#!/bin/sh
# XXX: SLOW AND STUPID
setvars() {
	sysc=$(echo "$line" | cut -f1 -d' ')
	ntype=$(echo "$line" | cut -f2 -d' ')
	name=$(echo "$line" | cut -f3 -d' ')
	args=$(echo "$line" | sed 's;.*(\(.*\)).*;\1;')
	if [ -z "$args" ]; then
		args="void"
		nargs="void"
	else
		a=$(printf -- '-e s;,;a%s;\n' $(seq 1 7))
		nargs=$(echo "$args," | sed $a -e 's;a\([0-9]\); a\1,;g' -e 's;,$;;')
	fi
}

sln() {
	[ "$ntype" = "void" ] && b1="" || b1="return ($ntype)"
	if [ "$args" = "void" ]; then
		b2="c_nix_syscall($sysc);"
	else
		a=$(echo "$nargs," | tr ' ' '\n' | sed -e '/.*,$/!d' -e '$s;,$;;g')
		b2=$(echo "c_nix_syscall($sysc, "$a");")
	fi
	cat <<EOF >src/sys/$name.c
#include <tertium/cpu.h>
#include <tertium/std.h>

$ntype
c_sys_$name($nargs)
{
	$b1$b2
}
EOF
}

mln() {
cat <<EOF >src/sys/$name.c
#include <tertium/cpu.h>
#include <tertium/std.h>

$ntype
c_sys_$name($args)
{
EOF
}

n_stat="true"
while IFS="" read -r line; do
	firstchr=$(echo -n "$line" | cut -c1)
	lastchar=$(echo -n "$line" | tail -c1)
	if [ -z "$line" ] || [ "$firstchr" = "#" ]; then
		true
	elif $n_stat; then
		setvars
		if [ "$lastchar" = "{" ]; then
			mln
			n_stat="false"
		else
			sln
		fi
	else
		if [ "$firstchr" = "}" ] && [ "$lastchar" = "}" ]; then
			echo "$lastchar" >>src/sys/$name.c
			n_stat="true"
		else
			echo "$line" >>src/sys/$name.c
		fi
	fi
done
