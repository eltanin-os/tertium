#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_cdb_find(ctype_cdb *p, char *k, usize n)
{
	c_cdb_findstart(p);
	return c_cdb_findnext(p, k, n);
}
