#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

static ctype_rune rangetab[] = {
	0x0115F, 0x01161,
	0x017B4, 0x017B6,
	0x0180B, 0x0180F,
	0x0200B, 0x02010,
	0x0202A, 0x0202F,
	0x02060, 0x02070,
	0x0FE00, 0x0FE10,
	0x0FFF0, 0x0FFF9,
	0x1BCA0, 0x1BCA4,
	0x1D173, 0x1D17B,
	0xE0000, 0xE1000,
};

static ctype_rune tab[] = {
	0x00AD,
	0x034F,
	0x061C,
	0x3164,
	0xFEFF,
	0xFFA0,
};

/* Ll, Lm, Lo, Lt, Lu */
int
c_utf8_isalpha(ctype_rune r)
{
	if (c_utf8_isupper(r) || c_utf8_islower(r) || c_utf8_istitle(r))
		return 1;
	if (UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	if (UTF8_SEARCH(&r, tab))
		return 1;
	return 0;
}
