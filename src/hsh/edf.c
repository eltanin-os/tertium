#include <tertium/cpu.h>
#include <tertium/std.h>

static void init(CHst *);
static void update(CHst *, char *, usize);
static void end(CHst *);

static CHmd md = {
	&init,
	&update,
	&end,
	nil,
};

CHmd *c_hsh_edf = &md;

static void
init(CHst *p)
{
	p->len = 0;
	p->st.x32[0] = 2111;
}

static void
update(CHst *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->st.x32[0] = (p->st.x32[0] + (*s++ - ' ')) * 2521;
}

static void
end(CHst *p)
{
	p->st.x32[0] ^= p->st.x32[0] << 16;
	p->st.x32[0] += p->st.x32[0] << 13;
	p->st.x32[0] ^= p->st.x32[0] >> 7;
	p->st.x32[0] += p->st.x32[0] << 9;
	p->st.x32[0] ^= p->st.x32[0] >> 8;
	p->st.x32[0] += p->st.x32[0] << 2;
}
