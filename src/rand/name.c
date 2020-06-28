#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar tab[] = \
    "-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";

char *
c_rand_name(char *s, usize n)
{
	s[--n] = 0;
	c_rand_data(s, n);
	while (n--)
		s[n] = tab[s[n] & 63];
	return s;
}
