#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_arr __exc_env;

ctype_status
c_exc_setenv(char *s, char *v)
{
	ctype_arr e;
	char *p;

	if (!s || !*s)
		return 0;

	if ((p = c_str_chr(s, C_USIZEMAX, '=')))
		*p = 0;

	c_mem_set(&e, sizeof(e), 0);
	if (c_dyn_fmt(&e, "%s", s) < 0)
		goto fail;

	if (v)
		if (c_dyn_fmt(&e, "=%s", v) < 0)
			goto fail;

	p = c_arr_data(&e);
	c_dyn_cat(&__exc_env, &p, 1, sizeof(char *));
	return 0;
fail:
	c_dyn_free(&e);
	return -1;
}
