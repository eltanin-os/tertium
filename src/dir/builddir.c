#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

#define RECLEN(dp) \
((c_std_offsetof(__fb_dirent, d_name)    + \
 c_str_len((dp)->d_name, C_USHRTMAX) + 1 + \
 (sizeof((dp)->d_ino) - 1)) & ~(sizeof((dp)->d_ino) - 1))

struct dir {
	ushort a;
	ushort n;
	uchar buf[2048];
};

ctype_node *
__dir_builddir(ctype_dir *p)
{
	__fb_dirent *d;
	ctype_dent *cur, *ep;
	ctype_node *np;
	struct dir dir;
	ctype_fd fd;
	int r;
	char rp[C_PATHMAX];

	cur = p->cur->p;

	if ((fd = c_sys_open(cur->path, C_OREAD | C_OCEXEC, 0)) < 0)
		return (void *)-1;

	c_mem_cpy(rp, cur->len, cur->path);
	rp[cur->len] = 0;

	c_mem_set(&dir, sizeof(dir), 0);
	np = nil;

	for (;;) {
		if (dir.n >= dir.a) {
			if ((r = c_std_syscall(SYS_getdents, fd,
			    dir.buf, sizeof(dir.buf))) < 0)
				goto err;
			if (!r)
				break;
			dir.a = r;
			dir.n = 0;
		}
		d = (void *)(dir.buf + dir.n);
		dir.n += RECLEN(d);

		if (!(p->opts & C_FSVDT) && C_ISDOT(d->d_name))
			continue;

		if (c_adt_lpush(&np, __dir_newfile(rp, d->d_name, p->opts)) < 0)
			goto err;

		ep = np->p;
		ep->info = __dir_info(p, ep);
		ep->parent = cur;
		ep->depth = cur->depth + 1;
		ep->__p = p->cur;
	}

	c_sys_close(fd);

	if (p->f)
		c_adt_lsort(&np, p->f);

	return np ? np->next : nil;
err:
	c_sys_close(fd);

	while (np)
		c_adt_lfree(c_adt_lpop(&np));

	return (void *)-1;
}
