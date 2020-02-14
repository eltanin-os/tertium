#include <tertium/cpu.h>
#include <tertium/std.h>

char *
c_rand_genseed(char *s, usize n)
{
	ctype_hst hs;
	ctype_taia now;
	int r;
	char buf[36];

	c_taia_now(&now);
	c_taia_pack(buf, &now);
	c_uint_32bigpack(buf + C_TAIA_PACK, c_sys_getpid());
	c_uint_64bigpack(buf + 4 + C_TAIA_PACK, (uintptr)s);
	c_uint_64bigpack(buf + 8 + C_TAIA_PACK, (uintptr)&n);
	c_hsh_all(&hs, c_hsh_edf, buf, sizeof(buf));
	while (n) {
		for (r = 0; r < 9; r++) {
			c_hsh_edf->update(&hs, buf, sizeof(buf));
			c_hsh_edf->end(&hs);
			c_hsh_digest(&hs, c_hsh_edf, buf + (r << 2));
		}
		n -= r = C_MIN(n, 4);
		c_mem_cpy(s + n, r, &hs.st.x32[0]);
	}
	return s;
}
