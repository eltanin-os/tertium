#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fcntl(ctype_fd fd, int cmd, ...)
{
	int r;
	va_list ap;

	va_start(ap, cmd);
	switch (cmd) {
	case C_FDUPFD:
	case C_FDUPFD_CEXEC:
	case C_FSETFD:
	case C_FSETFL:
	case C_FSETOWN:
		r = c_std_syscall(SYS_fcntl, cmd, fd, va_arg(ap, int));
		break;
	case C_FGETFD:
	case C_FGETFL:
	case C_FGETOWN:
		r = c_std_syscall(SYS_fcntl, cmd, fd);
		break;
	case C_FGETLK:
	case C_FSETLK:
	case C_FSETLKW:
		/* FALLTHROUGH (XXX) */
	default:
		r = c_std_syscall(SYS_fcntl, cmd, fd, va_arg(ap, void *));
		break;
	}
	va_end(ap);
	return r;
}
