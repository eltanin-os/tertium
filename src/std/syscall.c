#include <tertium/cpu.h>
#include <tertium/std.h>

#define ARGS(a)         \
a[0], a[1], a[2], a[3], \
a[4], a[5], a[6], a[7]

vlong
c_std_syscall_(vlong num, ...)
{
	va_list ap;
	int i;
	void *args[8];

	va_start(ap, num);
	for (i = 0; i < 8; ++i)
		args[i] = va_arg(ap, uintptr *);
	va_end(ap);

	return __asm_syscall(num, ARGS(args));
}
