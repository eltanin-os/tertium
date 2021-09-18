#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_nix_fdcopy(ctype_fd to, ctype_fd from)
{
	ctype_status r;

	if (to == from)
		return 0;

	do {
		r = c_sys_dup2(from, to);
	} while ((r < 0) && errno == C_EINTR);

	return r;
}
