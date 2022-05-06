#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar tab[] = \
"-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";

char *
c_rand_nameinc(ctype_rst *p, char *s, usize n)
{
	s[--n] = 0;
	c_rand_datainc(p, s, n);
	while (n--) s[n] = tab[s[n] & 63];
	return s;
}
