#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
makedir(char *s, uint mode)
{
	ctype_status sverr;
	sverr = errno;
	if (c_nix_mkdir(s, mode) < 0) {
		if (errno != C_ERR_EEXIST) return -1;
		errno = sverr;
	}
	return 0;
}

ctype_status
c_nix_mkpath(char *dir, uint dmode, uint mode)
{
	ctype_stat st;
	usize len;
	char buf[C_LIM_PATHMAX];
	char *s;

	if (c_nix_stat(&st, dir) < 0) {
		if (errno == C_ERR_ENOTDIR) return -1;
	} else {
		if (C_NIX_ISDIR(st.mode)) return 0;
		errno = C_ERR_ENOTDIR;
		return -1;
	}

	len = c_str_len(c_str_cpy(buf, sizeof(buf), dir), sizeof(buf));
	s = buf;
	if (*s == '/') ++s;

	for (;;) {
		if (!(s = c_mem_chr(s, len, '/'))) break;
		*s = 0;
		if (makedir(buf, dmode) < 0) return -1;
		*s++ = '/';
	}
	if (makedir(buf, mode) < 0) return -1;
	return 0;
}
