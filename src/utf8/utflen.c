#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_utf8_utflen(char *s)
{
	return c_utf8_utfnlen(s, -1);
}
