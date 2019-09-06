#include <tertium/cpu.h>
#include <tertium/std.h>

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
	nil,
};

ctype_hmd *c_hsh_edf = &md;

static void
init(ctype_hst *p)
{
	p->len = 0;
	p->st.x32[0] = 2111;
}

static void
update(ctype_hst *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->st.x32[0] = (p->st.x32[0] + (*s++ - ' ')) * 2521;
}

static void
end(ctype_hst *p)
{
	p->st.x32[0] ^= p->st.x32[0] << 16;
	p->st.x32[0] += p->st.x32[0] << 13;
	p->st.x32[0] ^= p->st.x32[0] >> 7;
	p->st.x32[0] += p->st.x32[0] << 9;
	p->st.x32[0] ^= p->st.x32[0] >> 8;
	p->st.x32[0] += p->st.x32[0] << 2;
}
