#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_isatty(int fd)
{
	ctype_stat st;

	if (c_sys_fstat(&st, fd) < 0)
		return -1;

	return C_ISCHR(st.mode);
}
