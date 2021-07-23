#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_std_fdcat(ctype_fd dest, ctype_fd src)
{
	size r;
	char buf[C_BIOSIZ];

	while ((r = c_sys_read(src, buf, sizeof(buf))) > 0)
		if (c_std_allrw(c_sys_write, dest, buf, r) < 0)
			return -2;

	return r < 0 ? -1 : 0;
}
