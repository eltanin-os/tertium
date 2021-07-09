#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
};

ctype_hmd *c_hsh_fletcher32 = &md;

static void
init(ctype_hst *p)
{
	p->curlen = 0;
	p->len = 0;
	p->st.x32[0] = 0;
	p->st.x32[1] = 0;
	p->st.x32[2] = 359;
}

static void
compress(ctype_hst *p, char *data)
{
	p->st.x32[1] += p->st.x32[0] += c_uint_16unpack(data);
	if (--p->st.x32[2]) {
		p->st.x32[0] = (p->st.x32[0] & 0xFFFF) + (p->st.x32[0] >> 16);
		p->st.x32[1] = (p->st.x32[1] & 0xFFFF) + (p->st.x32[1] >> 16);
		p->st.x32[2] = 359;
	}
}

static void
update(ctype_hst *p, char *data, usize n)
{
	c_hsh_update(compress, 2, p, data, n);
}

static void
end(ctype_hst *p, char *s)
{
	if (p->curlen > 2) {
		c_mem_set(p->buf + p->curlen, 2 - p->curlen, 0);
		compress(p, (char *)p->buf);
	}
	p->st.x32[0] = (p->st.x32[0] & 0xFFFF) + (p->st.x32[0] >> 16);
	p->st.x32[1] = (p->st.x32[1] & 0xFFFF) + (p->st.x32[1] >> 16);
	p->st.x32[0] |= p->st.x32[1] << 16;
	c_uint_32pack(s, p->st.x32[0]);
}
