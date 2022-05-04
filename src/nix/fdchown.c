#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdchown(ctype_fd fd, ctype_id uid, ctype_id gid)
{
	ctype_status r;

	do {
		r = c_sys_fchown(fd, uid, gid);
	} while ((r < 0) && errno == C_ERR_EINTR);

	return r;
}
