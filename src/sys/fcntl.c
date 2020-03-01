#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_fcntl(ctype_fd fd, int cmd, ...)
{
	ctype_status r;
	va_list ap;

	va_start(ap, cmd);
	switch (cmd) {
	case C_FDUPFD:
	case C_FDUPFD_CEXEC:
	case C_FSETFD:
	case C_FSETFL:
	case C_FSETOWN:
		r = c_std_syscall(SYS_fcntl, fd, va_arg(ap, int));
		break;
	case C_FGETFD:
	case C_FGETFL:
	case C_FGETOWN:
		r = c_std_syscall(SYS_fcntl, fd, 0);
		break;
	case C_FGETLK:
	case C_FSETLK:
	case C_FSETLKW:
		r = c_std_syscall(SYS_fcntl, fd, va_arg(ap, void *)); /* XXX */
		break;
	default:
		r = c_std_syscall(SYS_fcntl, fd, va_arg(ap, void *));
		break;
	}
	va_end(ap);
	return r;
}
