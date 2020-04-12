#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_mkadd(ctype_cdbmk *p, char *k, usize klen, char *s, usize dlen)
{
	ctype_hst hs;
	char buf[C_H32GEN_DIGEST];

	if (c_cdb_mkaddbegin(p, klen, dlen) < 0 ||
	    c_ioq_nput(&p->ioq, k, klen) < 0 ||
	    c_ioq_nput(&p->ioq, s, dlen) < 0)
		goto fail;

	c_hsh_all(&hs, c_hsh_djb, k, klen);
	c_hsh_digest(&hs, c_hsh_djb, buf);
	if (c_cdb_mkaddend(p, klen, dlen, c_uint_32unpack(buf)) < 0)
		goto fail;
	return 0;
fail:
	c_dyn_free(&p->hplist);
	return -1;
}
