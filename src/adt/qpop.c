#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_adt_qpop(CQueue *p, CArr *b, usize m, usize n)
{
	usize htt, len;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	htt = p->t >= p->h ? p->t - p->h : p->a - p->h + p->t;

	if (!htt)
		return 0;

	m *= n;
	m = C_MIN(m, htt);

	if (m > c_arr_avail(b)) {
		errno = C_ENOMEM;
		return -1;
	}

	len = p->h + m;
	len = len > p->a ? m - (len - p->a) : m;
	m -= len;

	c_arr_cat(b, p->p + p->h, len, sizeof(uchar));
	c_arr_cat(b, p->p, m, sizeof(uchar));
	p->h = m ? m : p->h + len;

	return 0;
}
