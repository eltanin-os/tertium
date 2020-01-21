#include <tertium/cpu.h>
#include <tertium/std.h>

static ulong t365[] = { 0, 365, 730, 1095 };
static ulong t36524[] = { 0, 36524UL, 73048UL, 109572UL };
static ulong tmon[] = { 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337 };

long
c_cal_datemjd(ctype_caldate *p)
{
	long d, m, y;

	d = (p->day - 678882L) + 146097L * (p->year / 400);
	m = p->month - 1;
	y = (p->year % 400);
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
	d += tmon[m] + (146097L * (y / 400));
	if ((y %= 400) < 0) {
		y += 400;
		d -= 146097L;
	}
	d += t365[y & 3];
	y >>= 2;
	d += 1461L * (y % 25);
	y /= 25;
	d += t36524[y & 3];
	return d;
}
