#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_std_errstr(char *s, usize n)
{
	usize i;
	char *p;

	p = c_std_getsyserr();
	n = C_MIN(n, C_ERRSIZ);
	for (i = 0; i < n; ++i) {
		s[i] ^= p[i];
		p[i] ^= s[i];
		s[i] ^= p[i];
	}
	errno = C_ECSTM;
}
