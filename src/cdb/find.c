#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_cdb_find(CCdb *p, char *k, usize n)
{
	c_cdb_findstart(p);
	return c_cdb_findnext(p, k, n);
}
