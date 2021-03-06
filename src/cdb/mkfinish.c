#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

ctype_status
c_cdb_mkfinish(ctype_cdbmk *p)
{
	struct hp *hp;
	struct hp *split;
	struct hp *hash;
	u32int count[256];
	u32int start[256];
	u32int k, len, u, where;
	usize i, j;
	usize n, msiz;
	char buf[8];
	char final[2048];

	c_mem_set(count, sizeof(count), 0);
	hp = c_arr_data(&p->hplist);
	n = c_arr_len(&p->hplist, sizeof(struct hp));
	for (i = 0; i < n; ++i)
		++count[hp[i].h & 255];

	msiz = 1;
	for (i = 0; i < 256; ++i)
		if ((u = count[i] << 1) > msiz)
			msiz = u;
	if ((msiz += n) > ((u32int)-1) / sizeof(struct hp))
		return (errno = C_ENOMEM, -1);

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
		c_uint_32pack(final + (i << 3), p->off);
		c_uint_32pack(final + (i << 3) + 4, len);
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
			if (C_OFLW_UA(u32int, p->off, 8)) {
				errno = C_ENOMEM;
				goto fail;
			}
			p->off += 8;
		}
	}
	if (c_ioq_flush(&p->ioq) < 0 ||
	    c_sys_seek(p->fd, 0, C_SEEKSET) < 0 ||
	    c_std_allrw(&c_sys_write, p->fd, final, sizeof(final)) < 0)
		goto fail;
	c_std_free(split);
	return 0;
fail:
	c_std_free(split);
	return -1;
}
