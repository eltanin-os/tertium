#!/bin/sh
# XXX: SLOW AND STUPID
printvars() {
	ntype=$(echo "$line" | cut -f2 -d' ')
	name=$(echo "$line" | cut -f3 -d' ')
	args=$(echo "$line" | sed -e 's;.*(\(.*\)).*;\1;' -e 's;[[:space:]].[a-zA-Z],;,;g')
	[ -z "$args" ] && args="void"
	printf '%s c_sys_%s(%s);\n' "$ntype" "$name" "$args"
}

n_stat="true"
while IFS="" read -r line; do
	firstchr=$(echo -n "$line" | cut -c1)
	lastchar=$(echo -n "$line" | tail -c1)
	if [ -z "$line" ] || [ "$firstchr" = "#" ]; then
		true
	elif $n_stat; then
		printvars
		if [ "$lastchar" = "{" ]; then
			n_stat="false"
		fi
	else
		if [ "$firstchr" = "}" ] && [ "$lastchar" = "}" ]; then
			n_stat="true"
		fi
	fi
done
