#include <tertium/cpu.h>
#include <tertium/std.h>

#define DEFOPTS (C_OCREATE|C_OEXCL|C_ORDWR)

ctype_fd
c_std_mktemp(char *s, usize n, uint opts)
{
	ctype_fd fd;
	usize len;
	char *p;

	if (!(p = c_str_rchr(s, n, 'X'))) {
		errno = C_EINVAL;
		return -1;
	}

	for (len = 0; *p == 'X'; --p, ++len) ;
	++p, ++len;

	for (;;) {
		c_rand_name(p, len);
		if (opts & C_OTMPDIR) {
			if (c_sys_mkdir(s, 0700) < 0) {
				if (errno != C_EEXIST)
					return -1;
				continue;
			}
			if ((fd = c_sys_open(s, C_OREAD | C_OEXCL, 0)) < 0)
				return -1;
		} else if ((fd = c_sys_open(s, DEFOPTS, 0600)) < 0) {
			if (errno != C_EEXIST)
				return -1;
			continue;
		}
		break;
	}
	if (opts & C_OTMPANON) {
		if (opts & C_OTMPDIR)
			c_sys_rmdir(s);
		else
			c_sys_unlink(s);
	}
	return fd;
}
