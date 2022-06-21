#include <tertium/cpu.h>
#include <tertium/std.h>

#define STRCPY(a, b) c_mem_cpy((a), sizeof((b)), (b))

char *
c_gen_dirname(char *s)
{
	usize n;

	if (!s) return nil;
	if (!*s) return STRCPY(s, ".");

	n = c_str_len(s, -1) - 1;
	for (; s[n] == '/'; --n) if (!n) return STRCPY(s, "/");
	for (; s[n] != '/'; --n) if (!n) return STRCPY(s, ".");
	for (; s[n] == '/'; --n) if (!n) return STRCPY(s, "/");

	s[n+1] = 0;
	return s;
}
