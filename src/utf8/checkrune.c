#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_utf8_checkrune(ctype_rune r)
{
	if (r > C_UTF8_RUNEMAX ||
	    (r & 0xFFFE) == 0xFFFE ||
	    (r >= 0xD800 && r <= 0xDFFF) ||
	    (r >= 0xFDD0 && r <= 0xFDEF) ||
	    (r > 0x10FFFF))
		return -1;
	return 0;
}
