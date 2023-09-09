#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_cpy(void *d, void *s, usize n)
{
	uchar *a, *b;

	if (s == d) return d;
	a = d;
	b = s;

	if (s > d) {
		for (; n; --n) *a++ = *b++;
	} else {
		a += n - 1;
		b += n - 1;
		for (; n; --n) *a-- = *b--;
	}
	return d;
}
