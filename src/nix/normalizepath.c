#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_nix_normalizepath(char *s, usize n)
{
	usize diff, off;
	int dir, found;
	char *prev;
	char *tmp;

	if (s[0] == '.' && s[1] == '/' && s[2]) c_str_cpy(s, n, s + 2);
	while ((tmp = c_str_str(s, n, "//"))) c_str_cpy(tmp, n, tmp + 1);
	while ((tmp = c_str_str(s, n, "/./"))) c_str_cpy(tmp, n, tmp + 2);
	/* strip "/../" only when redundant */
	do {
		off = found = 0;
		while ((tmp = c_str_str(s + off, n, "/../"))) {
			diff = tmp - s;
			off += diff;
			prev = c_str_rchr(s, diff - 1, '/');
			if (!prev) prev = s;
			if (!C_STR_CMP("../", prev + (*prev == '/'))) continue;
			diff = 3 + ((prev == s) && *s != '/');
			c_str_cpy(prev, n, tmp + diff);
			found = 1;
			break;
		}
	} while (found);
	return s;
}
