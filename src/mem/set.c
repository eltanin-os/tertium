#include <tertium/cpu.h>
#include <tertium/std.h>

void *
c_mem_set(void *v, usize n, int c)
{
	uchar *s;

	s = v;

	for (; n; n--)
		*s++ = c;

	__asm__ __volatile__(""::"r"(v):"memory");

	return v;
}
