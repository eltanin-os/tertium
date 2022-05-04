#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_lchown(char *s, ctype_id uid, ctype_id gid)
{
	ctype_status r;

	do {
		r = c_sys_lchown(s, uid, gid);
	} while ((r < 0) && errno == C_ERR_EINTR);

	return r;
}
