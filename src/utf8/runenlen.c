#include <tertium/cpu.h>
#include <tertium/std.h>

usize
c_utf8_runenlen(ctype_rune *p, usize len)
{
	usize n;

	n = 0;
	while (len--)
		n += c_utf8_runelen(*p++);

	return n;
}
