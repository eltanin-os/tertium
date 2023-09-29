#include <tertium/cpu.h>
#include <tertium/std.h>

static void *
copy(void *v, usize n, int c)
{
	volatile uchar *s;
	s = v;
	for (; n; --n) *s++ = c;
	return v;
}

/* Try to avoid compiler optimization */
static void *(* volatile set)(void *, usize, int) = copy;

void *
c_mem_set(void *v, usize n, int c)
{
	return set(v, n, c);
}
