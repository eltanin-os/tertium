#include <tertium/cpu.h>
#include <tertium/std.h>

#define RFLAGS (_TERTIUM_SYS_GRNDNONBLOCK|_TERTIUM_SYS_GRNDRANDOM)

static void
pseudoentropy(char *s, usize off, usize n)
{
	ctype_hst hs;
	ctype_rst r;
	ctype_taia now;
	usize i;
	char seed[32];

	/* seed */
	c_taia_now(&now);
	c_taia_pack(seed, &now);
	c_uint_32bigpack(seed+16, c_sys_getpid());
	c_uint_32bigpack(seed+20, c_sys_getppid());
	c_uint_64bigpack(seed+24, (uintptr)s);

	/* datainc genseed */
	c_hsh_siphash->init(&hs);
	c_hsh_siphash->update(&hs, s, n);
	c_hsh_siphash->update(&hs, seed, sizeof(seed));
	c_hsh_siphash->end(&hs, seed);
	/* extension */
	c_rand_setseed(&r, c_uint_64unpack(seed));
	c_rand_datainc(&r, s + off, n - off);
}

char *
c_rand_data(char *s, usize n)
{
	size r;
	r = c_sys_getrandom(s, n, RFLAGS);
	if (r < 0) r = 0;
	if ((usize)r < n) pseudoentropy(s, r, n);
	return s;
}
