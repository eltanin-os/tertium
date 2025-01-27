#include <tertium/cpu.h>
#include <tertium/std.h>

struct hash {
	ctype_hst *st;
	ctype_hmd *md;
};

static ctype_status
event(void *data, char *s, usize n)
{
	struct hash *h;
	h = data;
	h->md->update(h->st, s, n);
	return 0;
}

ctype_status
c_hsh_putfd(ctype_hst *h, ctype_hmd *md, ctype_fd fd, usize n)
{
	struct hash hash;
	hash.st = h;
	hash.md = md;
	return c_std_putfd(&hash, fd, n, &event);

}

ctype_status
c_hsh_putfile(ctype_hst *h, ctype_hmd *md, char *s)
{
	struct hash hash;
	hash.st = h;
	hash.md = md;
	return c_std_putfile(&hash, s, &event);
}
