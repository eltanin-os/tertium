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
	uchar  buf[2048];
};

static CNode *
builddir(CDir *p)
{
	__fb_dirent *d;
	CDent *cur, *ep;
	CNode *np;
	struct dir dir;
	int fd, r;
	char rp[C_PATHMAX];

	cur = p->cur->p;

	if ((fd = c_sys_open(cur->path, C_OREAD|C_OCEXEC, 0)) < 0)
		return nil;

	c_mem_cpy(rp, cur->len, cur->path);
	rp[cur->len] = 0;

	c_mem_set(&dir, sizeof(dir), 0);
	np = nil;

	for (;;) {
		if (dir.n >= dir.a) {
			if ((r = c_sys_call(SYS_getdents, fd,
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

CDent *
c_dir_read(CDir *p)
{
	CDent *ep;
	CNode *cur;

	cur = p->cur;
	ep  = cur->p;

	if (!cur)
		return nil;

	if (ep->info == C_FSD) {
		if (ep->instr == C_FSSKP) {
			ep->info = C_FSDP;
			return ep;
		}
		/* TODO: handle exclusive device */
		if ((p->child = builddir(p)) == (void *)-1) {
			ep->info = C_FSDNR;
			return ep;
		}
		if (!p->child) {
			ep->info = C_FSDP;
			return ep;
		}
		p->depth++;
		cur = p->child;
		p->cur = cur;
		ep = cur->p;
		return ep;
	}

	cur = cur->next;
	if (cur->prev) {
		p->cur = cur;
		ep = cur->p;
		return ep;
	}

	cur = ep->__p;
	if (cur) {
		while (p->cur)
			c_adt_lfree(c_adt_lpop(&p->cur));

		p->depth--;
		p->cur = cur;
		ep = cur->p;
		ep->info = C_FSDP;
		return ep;
	}

	while (p->cur)
		c_adt_lfree(c_adt_lpop(&p->cur));

	return nil;
}
