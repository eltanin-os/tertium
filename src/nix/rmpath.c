#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_rmpath(char *dir)
{
	char *s;
	char buf[C_LIM_PATHMAX];

	c_str_cpy(buf, sizeof(buf), dir);
	c_str_rtrim(buf, sizeof(buf), "/");
	for (;;) {
		if (c_nix_rmdir(buf) < 0)
			return -1;
		if (!(s = c_str_rchr(buf, sizeof(buf), '/')))
			break;
		*s = 0;
	}
	return 0;
}
