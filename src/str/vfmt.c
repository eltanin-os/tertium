#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_str_vfmt(char **sp, char *fmt, va_list ap)
{
	ctype_arr arr;
	size len;
	char *buf;
	va_list tmp;

	va_copy(tmp, ap);
	len = c_str_vfmtcnt(fmt, tmp) + 1;
	va_end(tmp);

	if (!(buf = c_std_alloc(len, sizeof(uchar)))) return (*sp = nil, -1);
	*sp = buf;
	c_arr_init(&arr, buf, len);
	return c_arr_vfmt(&arr, fmt, ap);
}
