#include <tertium/cpu.h>
#include <tertium/std.h>

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *);
static void digest(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
	&digest,
};

ctype_hmd *c_hsh_djb = &md;

static void
init(ctype_hst *p)
{
	p->len = 0;
	p->st.x32[0] = 5381;
}

static void
update(ctype_hst *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->st.x32[0] = (p->st.x32[0] + (p->st.x32[0] << 5)) ^ *s++;
}

static void
end(ctype_hst *p)
{
	(void)p;
}

static void
digest(ctype_hst *p, char *s)
{
	c_uint_32bigpack(s, p->st.x32[0]);
}
