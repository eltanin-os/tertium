#include <tertium/cpu.h>
#include <tertium/std.h>

#define debase(a) \
((((a) | 32) >= 'a') ? ((a) | 32) - 'a' + 10 : ((a) <= '9') ? (a) - '0' : -1)

#define rangeflow(a, b, c, d) \
(((a) > (b) || ((a) == (b) && (c) > (d))) ? 1 : 0)

uvlong
c_std_strtouvl(char *p, int b, uvlong l, uvlong h, char **e, int *r)
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

	o = h / b;
	m = o % b;
	a = v = 0;
	for (; *s; s++) {
		if ((c = debase(*s)) < 0)
			break;
		if (c >= b)
			break;
		if ((a = rangeflow(v, o, c, m)))
			break;
		v = (v * b) + c;
	}

	if (!e)
		e = &le;

	*e = (char *)s;
	if (*e[0]) {
		if (r)
			*r = -1;
		errno = (*e == p) ? C_ECANCELED : C_ENOTSUP;
	}

	if (a || (!n && l > v)) {
		if (r)
			*r = -1;
		errno = C_ERANGE;
	}

	return n ? -v : v;
}
