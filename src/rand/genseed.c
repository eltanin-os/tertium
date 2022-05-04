#include <tertium/cpu.h>
#include <tertium/std.h>

#define RFLAGS (_TERTIUM_SYS_GRNDNONBLOCK|_TERTIUM_SYS_GRNDRANDOM)

static void
pseudoentropy(char *s, usize n)
{
	ctype_hst hs;
	ctype_taia now;
	int r;
	char buf[36];

	c_hsh_edf->init(&hs);
	c_taia_now(&now);
	c_taia_pack(buf, &now);
	c_hsh_edf->update(&hs, buf, C_TAIA_PACK);
	c_hsh_edf->end(&hs, buf + C_TAIA_PACK);
	c_uint_32bigpack(buf, c_sys_getpid());
	c_hsh_edf->update(&hs, buf, sizeof(u32));
	c_hsh_edf->end(&hs, buf + C_TAIA_PACK + 4);
	c_uint_64bigpack(buf, (uintptr)s);
	c_hsh_edf->update(&hs, buf, sizeof(u64));
	c_hsh_edf->end(&hs, buf + C_TAIA_PACK + 12);
	c_uint_64bigpack(buf, (uintptr)&n);
	c_hsh_edf->update(&hs, buf, sizeof(u64));
	c_hsh_edf->end(&hs, buf + (C_TAIA_PACK + 20) - 4);
	while (n) {
		for (r = 0; r < 9; ++r) {
			c_hsh_edf->update(&hs, buf, sizeof(buf));
			c_hsh_edf->end(&hs, buf + (r << 2));
		}
		n -= r = C_STD_MIN(n, 4);
		c_hsh_edf->end(&hs, buf);
		c_mem_cpy(s + n, r, buf);
	}
}

char *
c_rand_genseed(char *s, usize n)
{
	size r;
	r = c_sys_getrandom(s, n, RFLAGS);
	if (r < 0) r = 0;
	pseudoentropy(s+r, n-r);
	return s;
}
