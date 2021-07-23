#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_ioq *
c_ioq_alloc(ctype_fd fd, usize n, ctype_iofn f)
{
	ctype_ioq *p;

	if (!(p = c_std_alloc(n + sizeof(*p), sizeof(uchar))))
		return nil;
	c_ioq_init(p, fd, (void *)((uchar *)p + sizeof(*p)), n, f);
	return p;
}
