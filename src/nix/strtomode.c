#include <tertium/cpu.h>
#include <tertium/std.h>

#define STANDARD_BITS (C_ISUID | C_ISGID | C_IRWXU | C_IRWXG | C_IRWXO)

/* TODO: Review this */
uint
c_nix_strtomode(char *s, uint mode, uint mask)
{
	uint clr, perm, who;
	uint m;
	char *end, op;

	m = c_std_strtouvl(s, 8, 0, 07777, &end, nil);
	if (!*end)
		return (m & C_ALLPERMS);
next:
	who = 0;
	for (; *s; ++s) {
		switch (*s) {
		case 'a':
			who |= STANDARD_BITS;
			continue;
		case 'g':
			who |= C_ISGID | C_IRWXG;
			continue;
		case 'o':
			who |= C_IRWXO;
			continue;
		case 'u':
			who |= C_ISUID | C_IRWXU;
			continue;
		}
		break;
	}
	if (who) {
		clr = who;
	} else {
		clr = C_ALLPERMS;
		who = ~mask;
	}

	switch (*s) {
	case '+':
	case '-':
	case '=':
		op = *s++;
		break;
	default:
		errno = C_EINVAL;
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
	if (mode & (C_IROTH << m))
		perm |= C_IRUSR | C_IRGRP | C_IROTH;
	if (mode & (C_IWOTH << m))
		perm |= C_IWUSR | C_IWGRP | C_IWOTH;
	if (mode & (C_IXOTH << m))
		perm |= C_IXUSR | C_IXGRP | C_IXOTH;
	++s;
	goto copy;
perm:
	switch (*s) {
	case 'X':
		if (C_ISDIR(mode) || mode & (C_IXUSR | C_IXGRP | C_IXOTH))
			perm |= C_IXUSR | C_IXGRP | C_IXOTH;
		break;
	case 'r':
		perm |= C_IRUSR | C_IRGRP | C_IROTH;
		break;
	case 's':
		perm |= C_ISUID | C_ISGID;
		break;
	case 't':
		perm |= C_ISVTX;
		break;
	case 'w':
		perm |= C_IWUSR | C_IWGRP | C_IWOTH;
		break;
	case 'x':
		perm |= C_IXUSR | C_IXGRP | C_IXOTH;
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
