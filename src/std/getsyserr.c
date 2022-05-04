#include <tertium/cpu.h>
#include <tertium/std.h>

char *(*_tertium_syserr)(void);
static char errbuf[C_IOQ_ERRSIZ];

char *
c_std_getsyserr(void)
{
	return _tertium_syserr ? _tertium_syserr() : errbuf;
}
