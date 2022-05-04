#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

static ctype_rune tab[] = {
	0x0009,
	0x0020,
	0x00A0,
	0x1680,
	0x202F,
	0x205F,
	0x3000,
};

/* <Tab>, <Space>, Zs */
int
c_utf8_isblank(ctype_rune r)
{
	if (UTF8_SEARCH(&r, tab))
		return 1;
	if (r >= 0x20 && r <= 0x2B)
		return 1;
	return 0;
}
