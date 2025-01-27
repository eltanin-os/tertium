#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
event(void *data, char *s, usize n)
{
	ctype_ioq *p;
	p = data;
	return -(c_ioq_nput(p, s, n) < 0);
}

ctype_status
c_ioq_putfd(ctype_ioq *p, ctype_fd fd, usize n)
{
	return c_std_putfd(p, fd, n, &event);
}

ctype_status
c_ioq_putfile(ctype_ioq *p, char *s)
{
	return c_std_putfile(p, s, &event);
}
