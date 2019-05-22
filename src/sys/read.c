#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_read(int f, void *p, usize n)
{
	size r;

	do {
		r = c_sys_call(SYS_read, f, p, n);
	} while ((r < 0) && (r == EINTR));

	return r;
}
