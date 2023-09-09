#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_cal_timeutc(ctype_caltime *p, ctype_tai *t)
{
	ctype_tai t2;
	u64 u;
	long s;
	int leap;

	c_mem_cpy(&t2, t, sizeof(t));
	leap = c_tai_leapsub(&t2);
	u = t2.x + 58486;
	s = u % 86400ULL;

	p->second = (s % 60) + leap;
	s /= 60;
	p->minute = s % 60;
	s /= 60;
	p->hour = s;

	u /= 86400ULL;
	c_cal_datefrommjd(&p->date, u - 53375995543064ULL);
	p->offset = 0;
}
