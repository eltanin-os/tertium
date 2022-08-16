#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_exc_wait(ctype_id id, ctype_status *status)
{
	ctype_status child, r;
	r = c_nix_waitpid(id, &child, 0);
	if (r <= 0) return -1;
	if (_TERTIUM_SYS_WIFEXITED(child)) {
		*status = _TERTIUM_SYS_WEXITSTATUS(child);
		return 1;
	}
	if (_TERTIUM_SYS_WIFSIGNALED(child)) {
		*status = _TERTIUM_SYS_WTERMSIG(child);
		return 2;
	}
	return 0;
}
