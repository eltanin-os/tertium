#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_sys_allrw(size (*op)(int, void *, usize), int f, void *p, usize n)
{
	size r, t;
	uchar *s;

	s = p;
	t = 0;

	while (n) {
		if ((r = op(f, p, n)) <= 0)
			return r;
		t += r;
		s += r;
		n -= r;
	}

	return t;
}
