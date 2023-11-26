#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

/* XXX */
static void
alignfree(void *p)
{
	c_std_free_(((void **)p)[-1]);
}

static void
traverse(void *t, void (*freeobj)(void *))
{
	ctype_kvent *p;
	struct node *q;
	uchar *s;
	if ((uintptr)(s = t) & 1) {
		q = (void *)(s - 1);
		traverse(q->child[0], freeobj);
		traverse(q->child[1], freeobj);
		alignfree(q);
	} else {
		p = (void *)s;
		if (freeobj) freeobj(p->v);
		c_std_free(p->k);
		alignfree(p);
	}
}

void
c_adt_kvfree(ctype_kvtree *t, void (*freeobj)(void *))
{
	if (!t->root) return;
	traverse(t->root, freeobj);
	t->root = nil;
}
