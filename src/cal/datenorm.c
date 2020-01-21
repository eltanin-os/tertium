#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_cal_datenorm(ctype_caldate *p)
{
	c_cal_datefrommjd(p, c_cal_datemjd(p));
}
