#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_chdir(char *s)
{
	int r;

	do {
		r = c_sys_call(SYS_chdir, s);
	} while((r < 0) && (r == EINTR));

	return r;
}
