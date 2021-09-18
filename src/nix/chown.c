#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_chown(char *s, ctype_id uid, ctype_id gid)
{
	ctype_status r;

	do {
		r = c_sys_chown(s, uid, gid);
	} while ((r < 0) && errno == C_EINTR);

	return r;
}
