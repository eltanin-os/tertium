#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_tai_fromtime(ctype_tai *t, ctype_time *tm)
{
	t->x = 4611686018427387914ULL + (u64)tm->sec;
}
