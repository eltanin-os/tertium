#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_utf8_runelen(ctype_rune r)
{
	if (c_utf8_checkrune(r) < 0)
		return 0;
	else if (r <= 0x00007F)
		return 1;
	else if (r <= 0x0007FF)
		return 2;
	else if (r <= 0x00FFFF)
		return 3;
	else if (r <= 0x1FFFFF)
		return 4;
	else if (r <= 0x3FFFFF)
		return 5;
	else
		return 6;
}
