#include <tertium/cpu.h>
#include <tertium/std.h>

#define RFLAGS (_TERTIUM_SYS_GRNDNONBLOCK|_TERTIUM_SYS_GRNDRANDOM)

static void
pseudoentropy(char *s, usize n)
{
	ctype_hst hs;
	ctype_tai now;
	usize i;
	char seed[16];

	/* seed */
	c_tai_now(&now);
	c_tai_pack(seed, &now);
	c_uint_32bigpack(seed+8, c_sys_getpid());
	c_uint_32bigpack(seed+12, (uintptr)s);
	/* hash */
	c_hsh_initk(&hs, seed, sizeof(seed));
	c_hsh_siphash->init(&hs);
	for (i = 0; i < n; i += 8) {
		c_hsh_siphash->update(&hs, s, n);
		c_hsh_siphash->end(&hs, seed);
		c_mem_cpy(s+i, C_STD_MIN(8, n - i), seed);
	}
}

char *
c_rand_data(char *s, usize n)
{
	size r;
	r = c_sys_getrandom(s, n, RFLAGS);
	if (r < 0) r = 0;
	if ((usize)r < n) pseudoentropy(s, n);
	return s;
}
