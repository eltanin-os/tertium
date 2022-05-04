#include <tertium/cpu.h>
#include <tertium/std.h>

#define ROPTS (C_NIX_OREAD|C_NIX_OEXCL)
#define DEFOPTS (C_NIX_OCREATE|C_NIX_OEXCL|C_NIX_ORDWR)

ctype_fd
c_nix_mktemp(char *s, usize n, uint opts)
{
	ctype_status (*func)(char *);
	ctype_fd fd;
	usize len;
	char *p;

	if (!(p = c_str_rchr(s, n, 'X'))) {
		errno = C_ERR_EINVAL;
		return -1;
	}

	for (len = 0; *p == 'X'; --p, ++len) ;
	++p, ++len;

	for (;;) {
		c_rand_name(p, len);
		if (opts & C_NIX_OTMPDIR) {
			if (c_nix_mkdir(s, 0700) < 0) {
				if (errno != C_ERR_EEXIST)
					return -1;
				continue;
			}
			if ((fd = c_nix_fdopen2(s, ROPTS)) < 0)
				return -1;
		} else if ((fd = c_nix_fdopen3(s, DEFOPTS, 0600)) < 0) {
			if (errno != C_ERR_EEXIST)
				return -1;
			continue;
		}
		break;
	}
	if (opts & C_NIX_OTMPANON) {
		func = (opts & C_NIX_OTMPDIR) ? c_sys_rmdir : c_sys_unlink;
		func(s);
	}
	return fd;
}
