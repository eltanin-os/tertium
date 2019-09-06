#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_write(ctype_fd fd, void *p, usize n)
{
	size r;

	do {
		r = c_sys_call(SYS_write, fd, p, n);
	} while ((r < 0) && (errno == C_EINTR));

	return r;
}
