#include <tertium/cpu.h>
#include <tertium/std.h>

/* XXX */
long
c_std_sysconf(int v)
{
	(void)v;
	errno = C_ERR_EINVAL;
	return -1;
}
