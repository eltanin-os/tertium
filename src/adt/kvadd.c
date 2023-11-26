#include <tertium/cpu.h>
#include <tertium/std.h>

#include "kv.h"

/* safe it from setalloc
 * XXX: should be another guarantee to add for the allocator interface
 * c_std_memalign(void *p, usize alignment, usize m, usize n)
 */
static void *
alignmem(usize alignment, usize n)
{
	uchar *data;
	void **p;
	usize off;

	off = alignment - 1 + sizeof(void *);

	data = c_std_alloc(n + off, sizeof(uchar));
	if (!data) return nil;

	p = (void **)(((uintptr)data + off) & ~(alignment - 1));
	p[-1] = (void *)(uintptr)data;
	return p;
}

static void *
alloc_leaf(uchar *k, usize n, void *v)
{
	ctype_kvent *p;

	if (!(p = alignmem(sizeof(void *), sizeof(*p)))) return nil;
	p->v = v;

	if (!(p->k = c_std_alloc(n, sizeof(uchar)))) {
		c_std_free(p);
		return nil;
	}
	c_mem_cpy(p->k, k, n);
	return p;
}

static void *
alloc_branch(uchar *u, usize len, void *v, u32 byte, u32 otherbits, int direction)
{
	struct node *newnode;
	ctype_kvent *p;

	newnode = alignmem(sizeof(void *), sizeof(*newnode));
	if (!newnode) return nil;

	if (!(p = alloc_leaf(u, len + 1, v))) {
		c_std_free(newnode);
		return nil;
	}

	newnode->byte = byte;
	newnode->otherbits = otherbits;
	newnode->child[1 - direction] = p;
	return newnode;
}

static u32
diffbit(u32 bits)
{
	bits |= bits >> 1;
	bits |= bits >> 2;
	bits |= bits >> 4;
	bits = (bits & ~(bits >> 1)) ^ 255;
	return bits;
}

ctype_status
c_adt_kvadd(ctype_kvtree *t, char *k, void *v)
{
	struct node *newnode, *q;
	ctype_kvent *p;
	usize len;
	u32 newbyte, newotherbits;
	int direction, newdirection;
	uchar *s, *u;
	uchar c;
	void **wherep;

	u = (void *)k;
	len = c_str_len(k, -1);
	if (!t->root) {
		if (!(t->root = alloc_leaf(u, len + 1, v))) return -1;
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

	newnode = alloc_branch(u, len, v, newbyte, newotherbits, newdirection);
	if (!newnode) return -1;

	/* insert node */
	wherep = &t->root;
	for (;;) {
		if (!((uintptr)(s = *wherep) & 1)) break;
		q = (void *)(s - 1);
		if (q->byte > newbyte ||
		    (q->byte == newbyte && q->otherbits > newotherbits)) {
			break;
		}
		c = (len > q->byte) ? u[q->byte] : 0;
		direction = (1 + (q->otherbits | c)) >> 8;
		wherep = q->child+direction;
	}
	newnode->child[newdirection] = *wherep;
	*wherep = (void *)((uchar *)newnode + 1);
	return 0;
}
