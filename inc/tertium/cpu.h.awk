# SYSCALL NUMBER - TYPE - NAME - ARGS
BEGIN {
}

# implicit
/^[A-Za-z_].*\(.*\)$/ {
	out=$2" c_sys_"$3
	$1=$2=$3=""
	if ($4 == "()") $4="(void)"
	sub(/^[ \t]+/, "")
	print out""$0";"
}

# explicit
/^[A-Za-z_].*\(.*\) / {
	out=$2" c_sys_"$3
	$1=$2=$3=""
	sub(/^[ \t]+/, "")
	sub(/ {$/, "")
	gsub(/ [A-Za-z]+,/, ",")
	gsub(/ [A-Za-z]+)/, ")")
	print out""$0";"
}

END {
}
