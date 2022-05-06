#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

void *
c_adt_kvget(ctype_kvtree *t, char *k)
{
	struct kv *p;
	usize len;
	if (!t->root) return nil;
	len = c_str_len(k, -1);
	p = walk(t->root, (void *)k, len);
	if (c_mem_cmp(k, len+1, p->k)) return nil;
	return p->v;
}
