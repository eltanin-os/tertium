#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

static void
traverse(void *t)
{
	struct kv *p;
	struct cbnode *q;
	uchar *s;
	if ((uintptr)(s = t) & 1) {
		q = (void *)(s - 1);
		traverse(q->child[0]);
		traverse(q->child[1]);
		c_std_free(q);
	} else {
		p = (void *)s;
		c_std_free(p->k);
		c_std_free(p);
	}
}

void
c_adt_kvfree(ctype_kvtree *t)
{
	if (!t->root) return;
	traverse(t->root);
	t->root = nil;
}
