#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_std_getopt(ctype_arg *p, int argc, char **argv, char *opts)
{
	int ch;
	char *opt, *s;

	s = argv[p->idx];
	if (!p->pos) {
		if (p->idx >= argc || s[0] != '-' || s[1] == '\0')
			return (p->opt = 0);
		if (s[1] == '-' && s[2] == '\0') {
			++p->idx;
			return (p->opt = 0);
		}
		++p->pos;
	}
	p->opt = ch = s[p->pos];
	++p->pos;
	if (!s[p->pos]) {
		p->pos = 0;
		++p->idx;
	}
	if (!(opt = c_str_chr(opts, -1, ch)) || *opt == ':')
		return (p->opt = '?');
	if (opt[1] == ':') {
		if (p->pos) {
			p->arg = s + p->pos;
			p->pos = 0;
		} else if (p->idx >= argc) {
			return (p->opt = ':');
		} else {
			p->arg = argv[p->idx];
		}
		++p->idx;
	}
	return ch;
}
