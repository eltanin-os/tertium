#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_nix_waitpid(ctype_id pid, int *status, uint opts)
{
	ctype_id id;

	do {
		id = c_sys_waitpid(pid, status, opts);
	} while ((id == (ctype_id)-1) && errno == C_EINTR);

	return id;
}
