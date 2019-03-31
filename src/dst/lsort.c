#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_dst_lsort(CNode **np, int (*f)(void *, void *))
{
	CNode *p, *q;
	CNode *e, *h, *t;
	int i, k, nm, ps, qs;

	if (!*np || !(*np)->prev)
		return;

	*np = (*np)->next;
	k   = 1;

	for (;;) {
		h    = p = *np;
		*np  = t = nil;
		nm = 0;

		while (p) {
			nm++;
			q  = p;
			ps = 0;
			for (i = 0; i < k; i++) {
				ps++;
				if (!(q = (q->next == h) ? nil : q->next))
					break;
			}
			qs = k;
			for (;;) {
				if (!(i = !!ps + (qs && q)))
					break;
				i = i-1 ? ((*f)(p->p, q->p) <= 0) : ps;
				if (i) {
					e = p;
					p = (p->next == h) ? nil : p->next;
					ps--;
				} else {
					e = q;
					q = (q->next == h) ? nil : q->next;
					qs--;
				}
				if (t)
					t->next = e;
				else
					*np = e;
				e->prev = t;
				t = e;
			}
			p = q;
		}
		t->next = *np;
		(*np)->prev = nil;
		if (!(nm-1)) {
			*np = t;
			break;
		}
		k <<= 1;
	}
}
