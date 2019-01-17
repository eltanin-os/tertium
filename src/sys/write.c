#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_write(int f, void *p, usize n)
{
	size   r, t;
	uchar *s;

	s = p;
	t = 0;

	while (n) {
		if ((r = c_sys_call(__NR_write, f, s, n)) < 0) {
			if (r == EINTR)
				continue;
			break;
		}
		t += r;
		s += r;
		n -= r;
	}

	return t;
}
