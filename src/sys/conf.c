#include <tertium/cpu.h>
#include <tertium/std.h>

long
c_sys_conf(int v)
{
	switch (v) {
	case _SC_ARG_MAX:
		return C_ARGMAX;
	case _SC_CHILD_MAX:
		return C_CHILDMAX;
	case _SC_HOST_NAME_MAX:
		return C_HOSTNAMEMAX;
	case _SC_LOGIN_NAME_MAX:
		return C_LOGINNAMEMAX;
	case _SC_NGROUPS_MAX:
		return C_NGROUPSMAX;
	case _SC_OPEN_MAX:
		return C_OPENMAX;
	case _SC_PAGESIZE:
		return C_PAGESIZE;
	case _SC_SYMLOOP_MAX:
		return C_SYMLOOPMAX;
	case _SC_TTY_NAME_MAX:
		return C_TTYNAMEMAX;
	case _SC_VERSION:
		return _POSIX_VERSION;
	}
	/*EINVAL*/
	return -1;
}
