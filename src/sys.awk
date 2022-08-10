# SYSCALL NUMBER - TYPE - NAME - ARGS
BEGIN {
}

# implicit
/^[A-Za-z_].*\(.*\)$/ {
	args=""
	out="#include <tertium/cpu.h>\n#include <tertium/std.h>\n\n"$2"\nc_sys_"$3
	count=0
	if ($2 == "void") ret=""; else ret="return "
	if ($4 == "()") {
		out=out"(void)\n{\n\t"ret"c_nix_syscall("$1");\n}"
	} else {
		for (i=4; i<=NF; i++) {
			count++
			tmp=substr($i, length($i), 1)
			if (i > 4) {
				args=args", "
				out=out" "
			}
			args=args"a"count
			out=out""substr($i, 1, length($i)-1)" a"count""tmp
		}
		out=out"\n{\n\t"ret"c_nix_syscall("$1", "args");\n}"
	}
	file=$3".c"
	print out > file
}

# explicit
/^[A-Za-z_].*\(.*\) / {
	file=$3".c"
	out="#include <tertium/cpu.h>\n#include <tertium/std.h>\n\n"$2"\nc_sys_"$3
	$1=$2=$3=""
	sub(/^[ \t]+/, "")
	print out""$0 > file
	flag=1
	next
}

/^}$/ {
	print > file
	flag=0
}

flag {
	print > file
}

END {
	fflush()
}
