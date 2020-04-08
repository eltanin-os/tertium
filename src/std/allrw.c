#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_std_allrw(ctype_iofn op, ctype_fd fd, void *p, usize n)
{
	size r;
	uchar *s;

	s = p;
	while (n) {
		if ((r = op(fd, p, n)) < 0)
			return r;
		if (!r)
			break;
		s += r;
		n -= r;
	}
	return s - (uchar *)p;
}
