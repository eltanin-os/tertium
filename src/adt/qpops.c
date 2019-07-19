#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_adt_qpops(CQueue *p, CArr *b)
{
	usize n, len;

	n = p->a - p->h;

	if ((len = c_str_len((char *)(p->p + p->h), n)) == n)
		len += c_str_len((char *)p->p, p->a);

	if (c_adt_qpop(p, b, len+1, sizeof(uchar)) < 0)
		return -1;

	--b->n;

	return 0;
}
