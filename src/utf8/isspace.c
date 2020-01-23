#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static ctype_rune rangetab[] = {
	0x00009, 0x0000E,
	0x0001C, 0x00021,
	0x02000, 0x0200B,
	0x02028, 0x0202A,
};

static ctype_rune tab[] = {
	0x00085,
	0x000A0,
	0x01680,
	0x0202F,
	0x0205F,
	0x03000,
};

/* Zs, Zl, Zp */
int
c_utf8_isspace(ctype_rune r)
{
	if (__UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	if (__UTF8_SEARCH(&r, tab))
		return 1;
	return 0;
}
