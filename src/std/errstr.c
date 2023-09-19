#include <tertium/cpu.h>
#include <tertium/std.h>

#define ERRBUF (_tertium_syserr ? _tertium_syserr() : errbuf)

char *(*_tertium_syserr)(void);
static char errbuf[C_IOQ_ERRSIZ];

static void
swap(uchar *a, uchar *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

static void
swapn(uchar *a, uchar *b, usize n)
{
	for (; n; ++a, ++b, --n) swap(a, b);
}

void
c_std_errstr(char *s, usize n)
{
	swapn((uchar *)s, (uchar *)ERRBUF, C_STD_MIN(C_IOQ_ERRSIZ, n));
	errno = C_ERR_ECSTM;
}
