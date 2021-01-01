#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fcntl(ctype_fd fd, int cmd, ...)
{
	ulong arg;
	va_list ap;

	va_start(ap, cmd);
	arg = va_arg(ap, ulong);
	va_end(ap);
	switch (cmd) {
	case C_FGETLK:
	case C_FSETLK:
	case C_FSETLKW:
		/* XXX */
		return c_std_syscall(SYS_fcntl, fd, cmd, (void *)arg);
	default:
		return c_std_syscall(SYS_fcntl, fd, cmd, arg);
	}
}
