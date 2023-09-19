#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_getln(ctype_arr *b, ctype_ioq *p)
{
	return c_ioq_getdelim(b, p, "\n");
}
