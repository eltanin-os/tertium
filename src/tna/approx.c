#include <tertium/cpu.h>
#include <tertium/std.h>

double
c_tna_approx(Taia *t)
{
	return c_tai_approx(&t->sec) + c_tna_frac(t);
}
