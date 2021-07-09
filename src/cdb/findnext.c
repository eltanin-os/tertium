#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
match(ctype_cdb *p, char *k, usize n, u32int off)
{
	usize len;
	char buf[1024];

	while (n) {
		len = C_MIN(n, sizeof(buf));
		if (c_cdb_read(p, buf, len, off) < 0)
			return -1;
		if (c_mem_cmp(buf, len, k))
			return 0;
		off += len;
		k += len;
		n -= len;
	}
	return 1;
}

ctype_status
c_cdb_findnext(ctype_cdb *p, char *k, usize n)
{
	u32int h;
	u32int off;
	char buf[8];

	if (!p->loop) {
		c_hsh_str(c_hsh_edf, k, n, buf);
		h = c_uint_32unpack(buf);
		if (c_cdb_read(p, buf, sizeof(buf), (h << 3) & 2047) < 0)
			return -1;
		if (!(p->hslots = c_uint_32unpack(buf + 4)))
			return 0;
		p->hpos = c_uint_32unpack(buf);
		p->khash = h;
		h = ((h >> 8) % p->hslots) << 3;
		p->kpos = p->hpos + h;
	}
	while (p->loop < p->hslots) {
		if (c_cdb_read(p, buf, sizeof(buf), p->kpos) < 0)
			return -1;
		if (!(off = c_uint_32unpack(buf + 4)))
			return 0;
		++p->loop;
		p->kpos += 8;
		if (p->kpos == p->hpos + (p->hslots << 3))
			p->kpos = p->hpos;
		if (c_uint_32unpack(buf) == p->khash) {
			if (c_cdb_read(p, buf, sizeof(buf), off) < 0)
				return -1;
			if (c_uint_32unpack(buf) == n) {
				switch (match(p, k, n, off + 8)) {
				case -1:
					return -1;
				case 1:
					p->dlen = c_uint_32unpack(buf + 4);
					p->dpos = off + 8 + n;
					return 1;
				}
			}
		}
	}
	return 0;
}
