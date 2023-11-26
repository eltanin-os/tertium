#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

static ctype_status
traverse(void *t, ctype_status (*func)(char *, void *))
{
	ctype_kvent *p;
	struct node *q;
	uchar *s;
	if ((uintptr)(s = (void *)t) & 1) {
		q = (void *)(s - 1);
		if (traverse(q->child[0], func) == -1) return -1;
		return traverse(q->child[1], func);
	} else {
		p = (void *)s;
		return func(p->k, p->v);
	}
	return 0;
}

ctype_status
c_adt_kvtraverse(ctype_kvtree *t, ctype_status (*func)(char *, void *))
{
	if (!t->root) return 0;
	return traverse(t->root, func);
}
