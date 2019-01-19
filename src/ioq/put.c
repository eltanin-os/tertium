#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_put(Ioq *p, char *s)
{
	return (c_ioq_nput(p, s, (char *)c_mem_chr(s, USIZE_MAX, 0)-s));
}
