#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_set(ctype_ioq *p, uint opts)
{
	if ((opts & ~__IOQ_OALL)) {
		errno = C_EINVAL;
		return -1;
	}
	p->opts |= opts;
	return 0;
}
