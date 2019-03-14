#include <tertium/cpu.h>
#include <tertium/std.h>

CArr newenv;

int
c_exc_setenv(char *s, char *v)
{
	CArr  e;
	char *p;

	if (!s || !*s)
		return 0;

	if ((p = c_str_chr(s, C_USIZEMAX, '=')))
		*p = 0;

	c_mem_set(&e, sizeof(e), 0);

	if (c_dyn_cats(&e, s) < 0)
		goto fail;

	if (v) {
		if (c_dyn_cats(&e, "=") < 0)
			goto fail;
		if (c_dyn_cats(&e, v)   < 0)
			goto fail;
	}

	p = c_arr_bget(&e, 0);
	c_dyn_cat(&newenv, &p, 1, sizeof(char *));
	return 0;
fail:
	c_dyn_free(&e);
	return -1;
}
