#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_cal_timetai(ctype_tai *t, ctype_caltime *p)
{
	long day, s;

	day = c_cal_datemjd(&p->date);
	s = ((p->hour * 60 + p->minute) - p->offset) * 60 + p->second;
	t->x = day * 86400ULL + 4611686014920671114ULL + (vlong)s;
	c_tai_leapadd(t, p->second == 60);
}
