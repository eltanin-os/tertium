#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

struct dir {
	ushort a;
	ushort n;
	uchar s[2048];
};

ctype_node *
_tertium_dir_builddir(ctype_dir *p)
{
	_tertium_type_dirent *d;
	ctype_dent *cur, *ep;
	ctype_node *np;
	struct dir dir;
	ctype_fd fd;
	int r;
	char rp[C_LIM_PATHMAX];

	cur = p->cur->p;
	if ((fd = c_nix_fdopen2(cur->path, C_NIX_OREAD | C_NIX_OCEXEC)) < 0)
		return BFAIL;

	c_mem_cpy(rp, cur->len, cur->path);
	rp[cur->len] = 0;

	c_mem_set(&dir, sizeof(dir), 0);
	np = nil;
	for (;;) {
		if (dir.n >= dir.a) {
			if ((r = c_sys_getdents(fd, dir.s, sizeof(dir.s))) < 0)
				goto err;
			if (!r)
				break;
			dir.a = r;
			dir.n = 0;
		}
		d = (void *)(dir.s + dir.n);
		dir.n += d->d_reclen;

		if (!(p->opts & C_DIR_FSVDT) && C_STD_ISDOT(d->d_name))
			continue;
		if (c_adt_lpush(&np,
		    _tertium_dir_newfile(rp, d->d_name, p->opts)) < 0)
			goto err;

		ep = np->p;
		ep->info = _tertium_dir_info(p, ep);
		ep->parent = cur;
		ep->depth = cur->depth + 1;
		ep->__p = p->cur;
	}
	c_nix_fdclose(fd);

	if (p->f)
		c_adt_lsort(&np, p->f);

	return np ? np->next : nil;
err:
	c_nix_fdclose(fd);

	while (np)
		c_adt_lfree(c_adt_lpop(&np));

	return BFAIL;
}
