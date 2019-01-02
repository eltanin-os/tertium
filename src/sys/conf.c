#include <tertium/cpu.h>
#include <tertium/std.h>

long
c_sys_conf(int v)
{
	switch (v) {
	case _SC_ARG_MAX:
		return ARG_MAX;
	case _SC_CHILD_MAX:
		return CHILD_MAX;
	case _SC_HOST_NAME_MAX:
		return HOST_NAME_MAX;
	case _SC_LOGIN_NAME_MAX:
		return LOGIN_NAME_MAX;
	case _SC_NGROUPS_MAX:
		return NGROUPS_MAX;
	case _SC_OPEN_MAX:
		return OPEN_MAX;
	case _SC_PAGESIZE:
		return PAGESIZE;
	case _SC_SYMLOOP_MAX:
		return SYMLOOP_MAX;
	case _SC_TTY_NAME_MAX:
		return TTY_NAME_MAX;
	case _SC_VERSION:
		return _POSIX_VERSION;
	}
	/*EINVAL*/
	return -1;
}
