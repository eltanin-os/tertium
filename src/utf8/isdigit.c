#include <tertium/cpu.h>
#include <tertium/std.h>

#include "internal.h"

static ctype_rune rangetab[] = {
	0x00030, 0x0003A,
	0x00660, 0x0066A,
	0x006F0, 0x006FA,
	0x007C0, 0x007CA,
	0x00966, 0x00970,
	0x009E6, 0x009F0,
	0x00A66, 0x00A70,
	0x00AE6, 0x00AF0,
	0x00B66, 0x00B70,
	0x00BE6, 0x00BF0,
	0x00C66, 0x00C70,
	0x00CE6, 0x00CF0,
	0x00D66, 0x00D70,
	0x00DE6, 0x00DF0,
	0x00E50, 0x00E5A,
	0x00ED0, 0x00EDA,
	0x00F20, 0x00F2A,
	0x01040, 0x0104A,
	0x01090, 0x0109A,
	0x017E0, 0x017EA,
	0x01810, 0x0181A,
	0x01946, 0x01950,
	0x019D0, 0x019DA,
	0x01A80, 0x01A8A,
	0x01A90, 0x01A9A,
	0x01B50, 0x01B5A,
	0x01BB0, 0x01BBA,
	0x01C40, 0x01C4A,
	0x01C50, 0x01C5A,
	0x0A620, 0x0A62A,
	0x0A8D0, 0x0A8DA,
	0x0A900, 0x0A90A,
	0x0A9D0, 0x0A9DA,
	0x0A9F0, 0x0A9FA,
	0x0AA50, 0x0AA5A,
	0x0ABF0, 0x0ABFA,
	0x0FF10, 0x0FF1A,
	0x104A0, 0x104AA,
	0x10D30, 0x10D3A,
	0x11066, 0x11070,
	0x110F0, 0x110FA,
	0x11136, 0x11140,
	0x111D0, 0x111DA,
	0x112F0, 0x112FA,
	0x11450, 0x1145A,
	0x114D0, 0x114DA,
	0x11650, 0x1165A,
	0x116C0, 0x116CA,
	0x11730, 0x1173A,
	0x118E0, 0x118EA,
	0x11C50, 0x11C5A,
	0x11D50, 0x11D5A,
	0x11DA0, 0x11DAA,
	0x16A60, 0x16A6A,
	0x16B50, 0x16B5A,
	0x1D7CE, 0x1D800,
	0x1E140, 0x1E14A,
	0x1E2F0, 0x1E2FA,
	0x1E950, 0x1E95A,
};

/* Nd */
int
c_utf8_isdigit(ctype_rune r)
{
	if (UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	return 0;
}
