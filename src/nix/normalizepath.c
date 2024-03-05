#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_nix_normalizepath(char *s, usize n)
{
	usize diff, off;
	int found;
	char *prev;
	char *tmp;

	if (s[0] == '.' && s[1] == '/' && s[2]) {
		for (off = 2; s[off] == '/'; ++off) ;
		c_str_cpy(s, n, s + off);
	}
	while ((tmp = c_str_str(s, n, "//"))) c_str_cpy(tmp, n, tmp + 1);
	while ((tmp = c_str_str(s, n, "/./"))) c_str_cpy(tmp, n, tmp + 2);
	/* strip "/../" only when redundant */
	do {
		off = found = 0;
		while ((tmp = c_str_str(s + off, n, "/../"))) {
			diff = tmp - s;
			if (!(off += diff)) {
				c_str_cpy(tmp + 1, n, tmp + 4);
			} else {
				if (!(prev = c_str_rchr(s, diff - 1, '/'))) {
					prev = s;
				}
				if (!C_STR_CMP("../", prev + (*prev == '/'))) {
					continue;
				}
				diff = 3 + (prev == s);
				c_str_cpy(prev, n, tmp + diff);
			}
			found = 1;
			break;
		}
	} while (found);
	return s;
}
