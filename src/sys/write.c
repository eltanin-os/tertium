#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_write(int f, void *p, usize n)
{
	size r;

	do {
		r = c_sys_call(SYS_write, f, p, n);
	} while ((r < 0) && (errno == EINTR));

	return r;
}
