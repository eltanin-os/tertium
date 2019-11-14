#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_ioq_put(ctype_ioq *p, char *s)
{
	return c_ioq_nput(p, s, c_str_len(s, C_USIZEMAX));
}
