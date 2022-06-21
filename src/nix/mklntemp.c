#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_mklntemp(char *s, usize n, char *target)
{
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
		if (c_nix_symlink(s, target) < 0) {
			if (errno != C_ERR_EEXIST) return -1;
			continue;
		}
		break;
	}
	return 0;
}
