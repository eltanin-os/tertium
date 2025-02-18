#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdfmt(ctype_fd fd, char *fmt, ...)
{
	va_list ap;
	ctype_status status;
	va_start(ap, fmt);
	status = c_nix_fdvfmt(fd, fmt, ap);
	va_end(ap);
	return status;
}
