#include <tertium/cpu.h>
#include <tertium/std.h>

/* Ll, Lm, Lo, Lt, Lu, Nd */
int
c_utf8_isalnum(ctype_rune r)
{
	return c_utf8_isalpha(r) || c_utf8_isdigit(r);
}
