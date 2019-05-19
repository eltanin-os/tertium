#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_cdb_mkaddbegin(CCdbmk *p, usize klen, usize dlen)
{
	char buf[8];

	c_uint_32pack(buf, klen);
	c_uint_32pack(buf+4, dlen);

	if (c_ioq_nput(&p->ioq, buf, 8) < 0)
		return -1;

	return 0;
}
