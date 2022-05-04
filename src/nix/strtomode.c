#include <tertium/cpu.h>
#include <tertium/std.h>

#define STANDARD_BITS \
(C_NIX_ISUID|C_NIX_ISGID|C_NIX_IRWXU|C_NIX_IRWXG|C_NIX_IRWXO)

/* TODO: Review this */
uint
c_nix_strtomode(char *s, uint mode, uint mask)
{
	uint clr, perm, who;
	uint m;
	char *end, op;

	m = c_std_strtouvl(s, 8, 0, 07777, &end, nil);
	if (!*end)
		return (m & C_NIX_ALLPERMS);
next:
	who = 0;
	for (; *s; ++s) {
		switch (*s) {
		case 'a':
			who |= STANDARD_BITS;
			continue;
		case 'g':
			who |= C_NIX_ISGID | C_NIX_IRWXG;
			continue;
		case 'o':
			who |= C_NIX_IRWXO;
			continue;
		case 'u':
			who |= C_NIX_ISUID | C_NIX_IRWXU;
			continue;
		}
		break;
	}
	if (who) {
		clr = who;
	} else {
		clr = C_NIX_ALLPERMS;
		who = ~mask;
	}

	switch (*s) {
	case '+':
	case '-':
	case '=':
		op = *s++;
		break;
	default:
		errno = C_ERR_EINVAL;
		return -1;
	}

	perm = 0;
copy:
	switch (*s) {
	case 'g':
		m = 3;
		break;
	case 'o':
		m = 0;
		break;
	case 'u':
		m = 6;
		break;
	default:
		goto perm;
	}
	if (mode & (C_NIX_IROTH << m))
		perm |= C_NIX_IRUSR | C_NIX_IRGRP | C_NIX_IROTH;
	if (mode & (C_NIX_IWOTH << m))
		perm |= C_NIX_IWUSR | C_NIX_IWGRP | C_NIX_IWOTH;
	if (mode & (C_NIX_IXOTH << m))
		perm |= C_NIX_IXUSR | C_NIX_IXGRP | C_NIX_IXOTH;
	++s;
	goto copy;
perm:
	switch (*s) {
	case 'X':
		if (C_NIX_ISDIR(mode) ||
		    mode & (C_NIX_IXUSR | C_NIX_IXGRP | C_NIX_IXOTH))
			perm |= C_NIX_IXUSR | C_NIX_IXGRP | C_NIX_IXOTH;
		break;
	case 'r':
		perm |= C_NIX_IRUSR | C_NIX_IRGRP | C_NIX_IROTH;
		break;
	case 's':
		perm |= C_NIX_ISUID | C_NIX_ISGID;
		break;
	case 't':
		perm |= C_NIX_ISVTX;
		break;
	case 'w':
		perm |= C_NIX_IWUSR | C_NIX_IWGRP | C_NIX_IWOTH;
		break;
	case 'x':
		perm |= C_NIX_IXUSR | C_NIX_IXGRP | C_NIX_IXOTH;
		break;
	default:
		goto apply;
	}
	++s;
	goto perm;
apply:
	switch (op) {
	case '+':
		mode |= (perm & who);
		break;
	case '-':
		mode &= ~(perm & who);
		break;
	case '=':
		mode &= ~clr;
		mode |= (perm & who);
	}
	if (*s == ',') {
		++s;
		goto next;
	}
	return mode;
}
