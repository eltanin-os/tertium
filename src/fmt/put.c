#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_fmt_put(ctype_fmt *p, char *s)
{
	return c_fmt_nput(p, s, c_str_len(s, -1));
}
