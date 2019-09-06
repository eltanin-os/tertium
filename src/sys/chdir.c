#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_chdir(char *s)
{
	ctype_status r;

	do {
		r = c_sys_call(SYS_chdir, s);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
