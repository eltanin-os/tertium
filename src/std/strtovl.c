#include <tertium/cpu.h>
#include <tertium/std.h>

#define debase(a) \
((((a) | 32) >= 'a') ? ((a) | 32) - 'a' + 10 : ((a) <= '9') ? (a) - '0' : -1)

#define rangeflow(a, b, c, d) \
(((a) > (b) || ((a) == (b) && (c) > (d))) ? 1 : 0)

vlong
c_std_strtovl(char *p, int b, vlong l, vlong h, char **e, int *r)
{
	uvlong v, o;
	int a, c, m, n;
	char *le;
	uchar *s;

	if ((uint)b > 36 || b == 1) {
		if (r)
			*r = -1;
		errno = C_EINVAL;
		return 0;
	}

	s = (uchar *)p;

	for (; c_chr_isspace(*s); s++) ;

	n = 0;

	if (*s == '-') {
		n = 1;
		s++;
	} else if (*s == '+') {
		s++;
	}

	if (b == 16 && *s == '0')
		b = 0;

	if (!b) {
		if (*s == '0') {
			s++;
			if ((*s | 32) == 'x') {
				b = 16;
				s++;
			} else {
				b = 8;
			}
		} else {
			b = 10;
		}
	}

	o = n ? -(uvlong)l : (uvlong)h;
	m = o % (uvlong)b;
	o /= (uvlong)b;

	a = 0;
	v = 0;

	for (; *s; s++) {
		if ((c = debase(*s)) < 0)
			break;
		if (c >= b)
			break;
		if (a < 0)
			continue;
		a = rangeflow(v, o, c, m);
		v = (v * b) + c;
	}

	if (!e)
		e = &le;

	*e = v ? (char *)s : p;
	if (*e[0]) {
		if (r)
			*r = -1;
		errno = (*e == p) ? C_ECANCELED : C_ENOTSUP;
	}

	if (a) {
		if (r)
			*r = -1;
		errno = C_ERANGE;
	}

	return n ? -v : v;
}
