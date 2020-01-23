#include <tertium/cpu.h>
#include <tertium/std.h>

/* !(Cc, Cf, Co, Ll, Lm, Lo, Lt, Lu, Nd, Zl, Zp, Zs) */
int
c_utf8_ispunct(ctype_rune r)
{
	return c_utf8_isgraph(r) && !c_utf8_isalnum(r);
}
