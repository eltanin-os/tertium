#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_mkadd(ctype_cdbmk *p, char *k, usize klen, char *s, usize dlen)
{
	char buf[C_HSH_H32DIG];

	if (c_cdb_mkaddbegin(p, klen, dlen) < 0 ||
	    c_ioq_nput(&p->ioq, k, klen) < 0 ||
	    c_ioq_nput(&p->ioq, s, dlen) < 0)
		goto fail;

	c_hsh_str(c_hsh_edf, k, klen, buf);
	if (c_cdb_mkaddend(p, klen, dlen, c_uint_32unpack(buf)) < 0)
		goto fail;
	return 0;
fail:
	c_dyn_free(&p->hplist);
	return -1;
}
