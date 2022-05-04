#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_std_errstr(char *s, usize n)
{
	usize i;
	char *p;

	p = c_std_getsyserr();
	n = C_STD_MIN(n, C_IOQ_ERRSIZ);
	for (i = 0; i < n; ++i) {
		s[i] ^= p[i];
		p[i] ^= s[i];
		s[i] ^= p[i];
	}
	errno = C_ERR_ECSTM;
}
