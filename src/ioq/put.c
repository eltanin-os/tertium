#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_ioq_put(CIoq *p, char *s)
{
	return (c_ioq_nput(p, s, (char *)c_mem_chr(s, C_USIZEMAX, 0)-s));
}
