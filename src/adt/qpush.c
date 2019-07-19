#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_adt_qpush(CQueue *p, void *v, usize m, usize n)
{
	usize htt, len;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	htt = p->t >= p->h ? p->t - p->h : p->a - p->h + p->t;
	m *= n;

	if (m > p->a - (htt + 1)) {
		errno = C_ENOMEM;
		return -1;
	}

	len = p->t + m;
	len = len > p->a ? m - (len - p->a) : m;
	m -= len;

	c_mem_cpy(p->p + p->t, len, v);
	c_mem_cpy(p->p, m, (uchar *)v + len);
	p->t = m ? m : p->t + len;
	p->p[p->t] = 0;

	return 0;
}
