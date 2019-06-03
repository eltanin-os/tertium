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

CHmd *c_hsh_djb = &md;

static void
init(CHst *p)
{
	p->len = 0;
	p->st.x32[0] = 5381;
}

static void
update(CHst *p, char *data, usize n)
{
	uchar *s;

	p->len += n;
	s = (uchar *)data;

	for (; n; n--)
		p->st.x32[0] = (p->st.x32[0] + (p->st.x32[0] << 5)) ^ *s++;
}

static void
end(CHst *p)
{
	(void)p;
}
