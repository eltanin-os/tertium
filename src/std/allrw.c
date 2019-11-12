#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_std_allrw(ctype_iofn op, ctype_fd fd, void *p, usize n)
{
	size r, t;
	uchar *s;

	s = p;
	t = 0;
	while (n) {
		if ((r = op(fd, p, n)) < 0)
			return r;
		if (!r)
			break;
		t += r;
		s += r;
		n -= r;
	}

	return t;
}
