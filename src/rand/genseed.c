#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_rand_genseed(char *s, usize n)
{
	ctype_hst hs;
	ctype_taia now;
	int r;
	char buf[20];

	c_taia_now(&now);
	c_taia_pack(buf, &now);
	c_uint_32bigpack(buf + C_TAIA_PACK, c_sys_getpid());
	c_uint_32bigpack(buf + 4 + C_TAIA_PACK, (uintptr)s);
	c_uint_32bigpack(buf + 8 + C_TAIA_PACK, (uintptr)&n);
	c_hsh_all(&hs, c_hsh_edf, buf, sizeof(buf));

	for (;;) {
		n -= r = C_MIN(n, 4);
		c_uint_32bigpack(buf, c_hsh_state0(&hs));
		c_mem_cpy(s + n, r, buf);

		if (!n)
			break;

		for (r = 0; r < 5; r++) {
			c_hsh_edf->update(&hs, buf, sizeof(buf));
			c_hsh_edf->end(&hs);
			c_uint_32bigpack(buf + (r << 2), c_hsh_state0(&hs));
		}
	}

	return s;
}
