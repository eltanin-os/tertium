#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_adt_qpop(CQueue *p, CArr *b, usize m, usize n)
{
	usize len;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	m *= n;

	if (!(len = c_arr_bytes(&p->mb)))
		return 0;

	m   = C_MIN(len, m);
	len = p->h + m;

	if (len > p->mb.a) {
		m   = len - p->mb.a;
		len = len - m;
	} else {
		len = 0;
	}

	if (len + m > c_arr_avail(b)) {
		errno = C_ENOMEM;
		return -1;
	}

	c_arr_cat(b, c_arr_get(&p->mb, p->h, sizeof(uchar)), m, sizeof(uchar));
	c_arr_cat(b, c_arr_data(&p->mb), len, sizeof(uchar));

	if (m >= c_arr_bytes(&p->mb)) {
		c_arr_trunc(&p->mb, 0, sizeof(uchar));
		p->h = 0;
	} else {
		p->mb.n -= m;
		p->h += m+1;
	}

	return 0;
}
