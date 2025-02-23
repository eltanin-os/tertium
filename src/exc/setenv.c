#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_arr _tertium_exc_env;

ctype_status
c_exc_setenv(char *s, char *v)
{
	ctype_arr e;
	ctype_status r;
	char *p;

	if (!(s && *s)) {
		errno = C_ERR_EINVAL;
		return -1;
	}

	if ((p = c_str_chr(s, -1, '='))) *p = 0;

	c_mem_set(&e, sizeof(e), 0);
	r = v ? c_dyn_fmt(&e, "%s=%s", s, v) : c_dyn_fmt(&e, "%s", s);
	if (r < 0) {
		c_dyn_free(&e);
		return -1;
	}
	p = c_arr_data(&e);
	return c_dyn_cat(&_tertium_exc_env, &p, 1, sizeof(char *));
}
