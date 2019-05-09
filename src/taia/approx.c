#include <tertium/cpu.h>
#include <tertium/std.h>

double
c_taia_approx(CTaia *t)
{
	return c_tai_approx(&t->sec) + c_taia_frac(t);
}
