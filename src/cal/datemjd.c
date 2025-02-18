#include <tertium/cpu.h>
#include <tertium/std.h>

static uint tmon[] = { 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337 };

long
c_cal_datemjd(ctype_caldate *p)
{
	long d, m, y;

	y = (p->year % 400);
	m = p->month - 1;
	d = (p->day - 678882L) + (p->year / 400) * 146097L;

	if (m >= 2) {
		m -= 2;
	} else {
		m += 10;
		--y;
	}
	y += (m / 12);
	if ((m %= 12) < 0) {
		m += 12;
		--y;
	}

	d += tmon[m] + ((y / 400) * 146097L);
	if ((y %= 400) < 0) {
		y += 400;
		d -= 146097L;
	}

	d += (y & 3) * 365;
	y >>= 2;

	d += (y % 25) * 1461L;
	y /= 25;

	d += (y & 3) * 36524;
	return d;
}
