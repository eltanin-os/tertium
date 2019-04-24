#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_errstr(char *s, usize n)
{
	usize i;
	char *p;
	uchar t;

	p = c_sys_getsyserr();
	n = C_MIN(n, C_ERRSIZ);

	for (i = 0; i < n; i++) {
		t = s[i];
		s[i] = p[i];
		p[i] = t;
	}

	errno = C_ECSTM;

	return 0;
}
