#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

static void
traverse(void *t, void (*freeobj)(void *))
{
	struct kv *p;
	struct cbnode *q;
	uchar *s;
	if ((uintptr)(s = t) & 1) {
		q = (void *)(s - 1);
		traverse(q->child[0], freeobj);
		traverse(q->child[1], freeobj);
		c_std_free(q);
	} else {
		p = (void *)s;
		if (freeobj) freeobj(p->k);
		c_std_free(p->v);
	}
}

void
c_adt_kvfree(ctype_kvtree *t, void (*freeobj)(void *))
{
	if (!t->root) return;
	traverse(t->root, freeobj);
	t->root = nil;
}
