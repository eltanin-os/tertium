#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_getln(ctype_ioq *p, ctype_arr *b)
{
	return c_ioq_getdelim(p, b, "\n");
}
