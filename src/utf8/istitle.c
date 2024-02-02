#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

static ctype_rune rangetab[] = {
	0x1F88, 0x1F90,
	0x1F98, 0x1FA0,
	0x1FA8, 0x1FB0,
};

static ctype_rune tab[] = {
	0x01C5,
	0x01C8,
	0x01CB,
	0x01F2,
	0x1FBC,
	0x1FCC,
	0x1FFC,
};

/* Lt */
int
c_utf8_istitle(ctype_rune r)
{
	if (UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	if (UTF8_SEARCH(&r, tab))
		return 1;
	return 0;
}
