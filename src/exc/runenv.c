#include <tertium/cpu.h>
#include <tertium/std.h>

extern ctype_arr __exc_env;

ctype_status
c_exc_runenv(char *prog, char **argv, char **envp)
{
	ctype_arr e, f;
	char **pv;
	char *path, *s;
	char buf[C_PATHMAX];

	c_mem_set(&e, sizeof(e), 0);

	if (c_dyn_cat(&e, __exc_env.p, __exc_env.n, sizeof(uchar)) < 0)
		return -1;

	if (envp)
		for (pv = envp; *pv; pv++)
			if (c_dyn_cat(&e, &*pv, 1, sizeof(*pv)) < 0)
				return -1;

	if ((path = c_str_chr(prog, C_USIZEMAX, '/')))
		return c_sys_exec(prog, argv, (char **)c_arr_data(&e));

	if (!(path = c_sys_getenv("PATH")))
		path = "/bin:/usr/bin:.";

	s = path;
	c_arr_init(&f, buf, sizeof(buf));

	for (;;) {
		c_arr_trunc(&f, 0, sizeof(uchar));
		if (!(s = c_str_chr(s, C_USIZEMAX, ':')))
			break;
		if (c_arr_fmt(&f, "%.*s/%s", s - path, path, prog) < 0)
			return -1;
		c_sys_exec(c_arr_data(&f), argv, (char **)c_arr_data(&e));
		if (!(errno == C_ENOENT || errno == C_EACCES ||
		    errno == C_EPERM || errno == C_EISDIR))
			break;
	}

	c_dyn_free(&e);
	return -1;
}
