#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

static u32
diffbit(u32 bits)
{
	bits |= bits >> 1;
	bits |= bits >> 2;
	bits |= bits >> 4;
	bits = (bits & ~(bits >> 1)) ^ 255;
	return bits;
}

static void *
createkv(uchar *k, usize n, void *v)
{
	struct kv *p;
	if (!(p = c_std_alloc(1, sizeof(*p))))
		return nil;
	if (!(p->k = c_std_alloc(n, sizeof(uchar)))) {
		c_std_free(p);
		return nil;
	}
	c_mem_cpy(p->k, k, n);
	p->v = v;
	return p;
}

ctype_status
c_adt_kvadd(ctype_kvtree *t, char *k, void *v)
{
	struct cbnode *q, *newnode;
	struct kv *p;
	usize len;
	u32 newbyte, newotherbits;
	int direction, newdirection;
	uchar *s, *u;
	uchar c;
	void **wherep;

	u = (void *)k;
	len = c_str_len(k, -1);
	if (!t->root) {
		if (!(t->root = createkv(u, len+1, v))) return -1;
		return 0;
	}
	p = walk(t->root, u, len);
	for (newbyte = 0; newbyte < len; ++newbyte) {
		if (p->k[newbyte] != u[newbyte]) {
			newotherbits = p->k[newbyte] ^ u[newbyte];
			goto newkey;
		}
	}
	if ((newotherbits = p->k[newbyte])) goto newkey;
	p->v = v;
	return 1;
newkey:
	/* create node */
	newotherbits = diffbit(newotherbits);
	newdirection = (1 + (newotherbits | (uchar)p->k[newbyte])) >> 8;
	if (!(newnode = c_std_alloc(1, sizeof(*newnode))))
		return -1;
	if (!(p = createkv(u, len+1, v))) {
		c_std_free(newnode);
		return -1;
	}
	newnode->byte = newbyte;
	newnode->otherbits = newotherbits;
	newnode->child[1 - newdirection] = p;
	/* insert node */
	wherep = &t->root;
	for (;;) {
		if (!((uintptr)(s = *wherep) & 1))
			break;
		q = (void *)(s - 1);
		if (q->byte > newbyte) break;
		if (q->byte == newbyte && q->otherbits > newotherbits) break;
		c = (len > q->byte) ? u[q->byte] : 0;
		direction = (1 + (q->otherbits | c)) >> 8;
		wherep = q->child+direction;
	}
	newnode->child[newdirection] = *wherep;
	*wherep = (void *)((uchar *)newnode + 1);
	return 0;
}
