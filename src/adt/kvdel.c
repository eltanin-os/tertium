#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

ctype_status
c_adt_kvdel(ctype_kvtree *t, char *k)
{
	struct cbnode *q;
	ctype_kvent *p;
	usize len;
	int direction;
	uchar *s, *u;
	uchar c;
	void **wherep, **whereq;

	if (!(s = t->root)) return -1;
	direction = 0;
	whereq = nil;
	wherep = &t->root;
	u = (void *)k;
	len = c_str_len(k, -1);
	while ((uintptr)s & 1) {
		whereq = wherep;
		q = (void *)(s - 1);
		c = (len > q->byte) ? u[q->byte] : 0;
		direction = (1 + (q->otherbits | c)) >> 8;
		wherep = q->child+direction;
		s = *wherep;
	}
	/* free key-val */
	p = (void *)s;
	if (c_str_cmp(k, len, p->k)) return -1;
	c_std_free(p->k);
	c_std_free(p);
	/* free node */
	if (!whereq) {
		t->root = nil;
		return 0;
	}
	*whereq = q->child[1 - direction];
	c_std_free(q);
	return 0;
}
