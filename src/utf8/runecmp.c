#include <tertium/cpu.h>
#include <tertium/std.h>

static int
rangecmp(ctype_rune k, ctype_rune *p)
{
	return (k >= p[0] && k <= p[1]) ? 0 : k - p[0];
}

int
__utf8_rangecmp(void *va, void *vb)
{
	return rangecmp(*(ctype_rune *)va, vb);
}

int
__utf8_cmp(void *va, void *vb)
{
	return *(ctype_rune *)va - *(ctype_rune *)vb;
}
