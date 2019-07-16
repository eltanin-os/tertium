#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

CNode *
__dir_newfile(char *path, char *name, uint opts)
{
	CNode *p;
	CDent *ep;
	usize  len;
	usize  plen;
	ushort nlen;
	uchar *sp;

	plen = c_str_len(path, C_USIZEMAX);
	nlen = c_str_len(name, C_USHRTMAX);
	len  = sizeof(*p) + sizeof(*ep) + plen + nlen + 1;
	if (!(opts & C_FSNOI))
		len += sizeof(CStat);

	if (!(sp = c_std_calloc(1, len)))
		return nil;

	p = (void *)sp;
	sp += sizeof(*p);

	ep = p->p = (void *)sp;
	sp += sizeof(*ep);

	ep->path = (void *)sp;
	sp += plen + nlen + 1;

	if (!(opts & C_FSNOI))
		ep->statp = (void *)sp;

	if (plen) {
		c_mem_cpy(ep->path, plen, path);
		if (!(ep->path[plen-1] == '/')) {
			ep->path[plen] = '/';
			ep->path[++plen] = 0;
		}
		ep->name = ep->path + plen;
		c_mem_cpy(ep->name, nlen, name);
		ep->len = plen + nlen;
		ep->nlen = nlen;
	} else {
		c_mem_cpy(ep->path, nlen, name);
		if (!(ep->path[nlen-1] == '/')) {
			ep->path[nlen] = '/';
			ep->path[++nlen] = 0;
		}
		ep->name = ep->path;
		ep->len = nlen;
		ep->nlen = nlen;
	}

	return p;
}
