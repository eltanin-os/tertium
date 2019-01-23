#include <tertium/cpu.h>
#include <tertium/std.h>

double
c_tna_frac(CTaia *t)
{
	return (t->atto * 0.000000001 + t->nano) * 0.000000001;
}
