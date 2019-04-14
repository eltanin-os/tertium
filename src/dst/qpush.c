#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_dst_qpush(CQueue *p, void *v, usize m, usize n)
{
	usize len, tail;

	if (C_OFLW_UM(usize, m, n)) {
		errno = C_EOVERFLOW;
		return -1;
	}

	m *= n;

	if (m > c_arr_avail(&p->mb)) {
		errno = C_ENOMEM;
		return -1;
	}

	if ((tail = p->h + c_arr_bytes(&p->mb)) > p->mb.a)
		tail = tail - p->mb.a;

	len = tail + m;

	if (len > p->mb.a) {
		m   = len - p->mb.a;
		len = len - m;
		p->mb.p[tail+len] = 0;
	} else {
		len = 0;
		p->mb.p[tail+m] = 0;
	}

	c_mem_cpy(c_arr_bget(&p->mb, tail), m, v);
	c_mem_cpy(c_arr_bget(&p->mb, 0), len, (uchar *)v+m);
	p->mb.n += len + m;

	return 0;
}
