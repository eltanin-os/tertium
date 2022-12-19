#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

ctype_node *
_tertium_dir_newfile(char *path, char *name, uint opts)
{
	ctype_node *p;
	ctype_dent *ep;
	usize len, nlen, plen;
	int dir;
	uchar *sp;

	nlen = c_str_len(name, C_LIM_USIZEMAX);
	if (!(plen = c_str_len(path, C_LIM_USIZEMAX))) {
		dir = name[nlen - 1] == '/';
		for (; nlen > 1 && name[nlen - 1] == '/'; --nlen) ;
		if (nlen > 1) {
			path = name;
			if (!(name = c_mem_rchr(path, nlen, '/'))) {
				name = path;
				plen = 0;
			} else {
				++name;
				plen = name - path;
				nlen -= plen;
			}
			if (dir) {
				name[nlen++] = '/';
				name[nlen] = 0;
			}
		}
	}

	len = sizeof(*p) + sizeof(*ep) + plen + nlen + 2;
	if (!(opts & C_DIR_FSNOI))
		len += sizeof(ctype_stat) + 16;
	if (!(sp = c_std_alloc(len, sizeof(uchar))))
		return nil;

	p = (void *)sp;
	p->prev = nil;
	p->next = p;
	sp += sizeof(*p);
	ep = p->p = (void *)sp;
	sp += sizeof(*ep);
	c_mem_set(ep, sizeof(*ep), 0);
	ep->path = (void *)sp;
	sp += plen + nlen + 2;

	if (!(opts & C_DIR_FSNOI))
		ep->stp = (void *)((uintptr)(sp + 16) & ~16);

	if (plen) {
		c_mem_cpy(ep->path, plen, path);
		if (ep->path[plen - 1] != '/') ep->path[plen++] = '/';
	}
	ep->name = ep->path + plen;
	c_mem_cpy(ep->name, nlen, name);
	ep->name[nlen] = 0;
	ep->len = plen + nlen;
	ep->nlen = nlen;
	return p;
}
