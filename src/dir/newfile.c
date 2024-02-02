#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

ctype_node *
_tertium_dir_newfile(char *dir, char *name, uint opts)
{
	ctype_arr arr;
	ctype_node *p;
	ctype_dent *ep;
	usize n, nlen;
	uchar *pool;

	/* allocate a pool and set pointers */
	nlen = c_str_len(dir, -1) + c_str_len(name, -1) + 2;
	n = sizeof(*p) + sizeof(*ep) + nlen;
	if (!(opts & C_DIR_FSNOI)) n += sizeof(ctype_stat) + 16; /* mem align */
	if (!(pool = c_std_alloc(n, sizeof(uchar)))) return nil;

	p = (void *)pool;
	pool += sizeof(*p);
	p->prev = nil;
	p->next = p;

	ep = p->p = (void *)pool;
	pool += sizeof(*ep);
	c_mem_set(ep, sizeof(*ep), 0);

	ep->path = (void *)pool;
	pool += nlen;

	if (!(opts & C_DIR_FSNOI)) {
		ep->stp = (void *)((uintptr)(pool + 16) & ~16);
	}

	c_arr_init(&arr, ep->path, nlen);
	c_arr_fmt(&arr, "%s%s%s", dir, dir[0] ? "/" : "", name);
	n = c_arr_bytes(&arr);

	/* normalize path (ensure reproducibility) and recalculate lengths */
	if (!(opts & C_DIR_FSNON)) {
		n = c_str_len(c_nix_normalizepath(ep->path, n), n);
	} else {
		nlen = ep->path[n - 1] == '/';
		n = c_str_len(c_str_rtrim(ep->path, n, "/"), n);
		if (nlen) ep->path[n++ - 1] = '/';
	}
	if (n > 1) {
		nlen = ep->path[n - 1] == '/';
		if ((name = c_mem_rchr(ep->path, n - nlen, '/'))) {
			++name;
			nlen = n - (name - ep->path);
		} else {
			nlen = n;
		}
	} else {
		nlen = n;
	}

	/* start dir entry */
	ep->name = ep->path + (n - nlen);
	ep->len = n;
	ep->nlen = nlen;
	return p;
}
