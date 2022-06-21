#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

static void
traverse(void *t, void (*func)(char *, void *))
{
	struct kv *p;
	struct cbnode *q;
	uchar *s;
	if ((uintptr)(s = (void *)t) & 1) {
		q = (void *)(s - 1);
		traverse(q->child[0], func);
		traverse(q->child[1], func);
	} else {
		p = (void *)s;
		func(p->k, p->v);
	}
}

void
c_adt_kvtraverse(ctype_kvtree *t, void (*func)(char *, void *))
{
	if (!t->root) return;
	traverse(t->root, func);
}
