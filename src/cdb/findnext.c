#include <tertium/cpu.h>
#include <tertium/std.h>

static int
match(CCdb *p, char *k, usize n, u32int off)
{
	usize len;
	char  buf[1024];

	while (n) {
		len = C_MIN(n, sizeof(buf));
		if (c_cdb_read(p, buf, len, off) < 0)
			return -1;
		if (c_mem_cmp(buf, len, k))
			return 0;
		off += len;
		k   += len;
		n   -= len;
	}

	return 1;
}

int
c_cdb_findnext(CCdb *p, char *k, usize n)
{
	CH32st hs;
	u32int u;
	u32int off;
	char   buf[8];

	if (!p->loop) {
		c_hsh_all(&hs, c_hsh_djb, k, n);
		if (c_cdb_read(p, buf, 8, (hs.state[0] << 3) & 2047) < 0)
			return -1;
		if (!(p->hslots = c_uint_32unpack(buf + 4)))
			return 0;
		p->hpos  = c_uint_32unpack(buf);
		p->khash = hs.state[0];
		p->kpos  = p->hpos + (((hs.state[0] >> 8) % p->hslots) << 3);
	}

	while (p->loop < p->hslots) {
		if (c_cdb_read(p, buf, 8, p->kpos) < 0)
			return -1;
		if (!(off = c_uint_32unpack(buf + 4)))
			return 0;
		p->loop++;
		p->kpos += 8;
		if (p->kpos == p->hpos + (p->hslots << 3))
			p->kpos = p->hpos;
		if ((u = c_uint_32unpack(buf)) == p->khash) {
			if (c_cdb_read(p, buf, 8, off) < 0)
				return -1;
			if ((u = c_uint_32unpack(buf)) == n) {
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
