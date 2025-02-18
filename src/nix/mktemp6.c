#include <tertium/cpu.h>
#include <tertium/std.h>

#define ROPTS (C_NIX_OREAD|C_NIX_OEXCL)

ctype_fd
c_nix_mktemp6(char *s, usize n, uint opts, uint fdopts, uint fdmode, char *(*rand)(char *, usize))
{
	ctype_status (*func)(char *);
	ctype_fd fd;
	usize len;
	char *p;

	fdopts |= (C_NIX_OCREATE|C_NIX_OEXCL|C_NIX_ORDWR);

	if (!(p = c_str_rchr(s, n, 'X'))) {
		errno = C_ERR_EINVAL;
		return -1;
	}

	for (len = 0; n && *p == 'X'; --n, --p, ++len) ;
	++p, ++len;

	for (;;) {
		rand(p, len);
		if (opts & C_NIX_OTMPDIR) {
			if (c_nix_mkdir(s, fdmode) < 0) {
				if (errno != C_ERR_EEXIST) return -1;
				continue;
			}
			fd = c_nix_fdopen2(s, ROPTS);
			if (fd < 0) return -1;
		} else if ((fd = c_nix_fdopen3(s, fdopts, fdmode)) < 0) {
			if (errno != C_ERR_EEXIST) return -1;
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
