#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_cdb_mkadd(CCdbmk *p, char *k, usize klen, char *s, usize dlen)
{
	CHst hs;

	if (c_cdb_mkaddbegin(p, klen, dlen) < 0)
		goto fail;

	if (c_ioq_nput(&p->ioq, k, klen) < 0)
		goto fail;

	if (c_ioq_nput(&p->ioq, s, dlen) < 0)
		goto fail;

	c_hsh_all(&hs, c_hsh_djb, k, klen);
	if (c_cdb_mkaddend(p, klen, dlen, c_hsh_state0(&hs)) < 0)
		goto fail;

	return 0;
fail:
	c_dyn_free(&p->hplist);
	return -1;
}

