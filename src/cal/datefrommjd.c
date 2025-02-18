#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_cal_datefrommjd(ctype_caldate *p, long day)
{
	long month, year;
	long q;

	year = day / 146097L;
	day = (day % 146097L) + 678881L;

	q = day / 146097L;
	year += q;
	day -= q * 146097L;

	year <<= 2;

	if (day == 146096L) {
		year += 3;
		day += 36524L;
	} else {
		year += day / 36524L;
		day %= 36524L;
	}

	year = ((year * 25) + day / 1461) << 2;
	day %= 1461;

	if (day == 1460) {
		year += 3;
		day = 365;
	} else {
		year += day / 365;
		day %= 365;
	}

	day *= 10;
	month = (day + 5) / 306;
	day = ((day + 5) % 306) / 10;

	if (month >= 10) {
		month -= 10;
		++year;
	} else {
		month += 2;
	}
	++day;
	++month;

	p->day = day;
	p->month = month;
	p->year = year;
}
