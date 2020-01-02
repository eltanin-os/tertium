#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_ioq *
c_ioq_alloc(ctype_fd fd, usize n, ctype_iofn f)
{
	ctype_ioq *p;
	char *buf;

	if (!(p = c_std_alloc(1, sizeof(*p))))
		return nil;

	if (!(buf = c_std_alloc(n, sizeof(uchar)))) {
		c_std_free(p);
		return nil;
	}

	c_ioq_init(p, fd, buf, n, f);
	return p;
}
