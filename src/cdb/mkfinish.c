#include <tertium/cpu.h>
#include <tertium/std.h>

struct hp {
	u32 h;
	u32 p;
};

ctype_status
c_cdb_mkfinish(ctype_cdbmk *p)
{
	struct hp *hp;
	struct hp *split;
	struct hp *hash;
	u32 count[256];
	u32 start[256];
	u32 k, len, u, where;
	usize i, j;
	usize n, msiz;
	char buf[8];
	char end[2048];

	c_mem_set(count, sizeof(count), 0);
	hp = c_arr_data(&p->hplist);
	n = c_arr_len(&p->hplist, sizeof(struct hp));
	for (i = 0; i < n; ++i)
		++count[hp[i].h & 255];

	msiz = 1;
	for (i = 0; i < 256; ++i)
		if ((u = count[i] << 1) > msiz)
			msiz = u;
	if ((msiz += n) > (u32)-1 / sizeof(struct hp)) {
		errno = C_ERR_ENOMEM;
		return -1;
	}

	if (!(split = c_std_alloc(msiz, sizeof(struct hp))))
		return -1;
	u = 0;
	for (i = 0; i < 256; ++i)
		start[i] = u += count[i];
	i = n;
	while (i--)
		split[--start[hp[i].h & 255]] = hp[i];
	c_dyn_free(&p->hplist);
	hp = split + n;
	for (i = 0; i < 256; ++i) {
		k = count[i];
		len = k << 1;
		c_uint_32pack(end + (i << 3), p->off);
		c_uint_32pack(end + (i << 3) + 4, len);
		c_mem_set(hp, len * sizeof(*hp), 0);
		hash = split + start[i];
		for (j = 0; j < k; ++j) {
			where = (hash->h >> 8) % len;
			while (hp[where].p)
				if (++where == len)
					where = 0;
			hp[where] = *hash++;
		}
		for (j = 0; j < len; ++j) {
			c_uint_32pack(buf, hp[j].h);
			c_uint_32pack(buf + 4, hp[j].p);
			if (c_ioq_nput(&p->ioq, buf, 8) < 0)
				goto fail;
			if (C_STD_OVERFLOWA(u32, p->off, 8)) {
				errno = C_ERR_ENOMEM;
				goto fail;
			}
			p->off += 8;
		}
	}
	if (c_ioq_flush(&p->ioq) < 0) goto fail;
	if (c_nix_seek(p->fd, 0, C_NIX_SEEKSET) < 0) goto fail;
	if (c_nix_allrw(&c_nix_fdwrite, p->fd, end, sizeof(end)) < 0) goto fail;
	c_std_free(split);
	return 0;
fail:
	c_std_free(split);
	return -1;
}
