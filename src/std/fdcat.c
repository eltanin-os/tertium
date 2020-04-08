#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_std_fdcat(ctype_fd target, ctype_fd source)
{
	size r;
	char buf[C_BIOSIZ];

	while ((r = c_sys_read(source, buf, sizeof(buf))) > 0)
		if (c_std_allrw(c_sys_write, target, buf, r) < 0)
			return -1;

	return r < 0 ? -1 : 0;
}
