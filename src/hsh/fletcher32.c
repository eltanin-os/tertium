#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
	nil,
};

ctype_hmd *c_hsh_fletcher32 = &md;

static void
init(ctype_hst *p)
{
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
	__hsh_update(compress, 2, p, data, n);
}

static void
end(ctype_hst *p)
{
	uint r;

	r = p->len % 2;

	if (r) {
		c_mem_set(p->buf + r, 2 - r, 0);
		compress(p, (char *)p->buf);
	}

	p->st.x32[0] = (p->st.x32[0] & 0xFFFF) + (p->st.x32[0] >> 16);
	p->st.x32[1] = (p->st.x32[1] & 0xFFFF) + (p->st.x32[1] >> 16);
	p->st.x32[0] = p->st.x32[0] | p->st.x32[1] << 16;
}
