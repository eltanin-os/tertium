#include <tertium/cpu.h>
#include <tertium/std.h>

extern CArr newenv;

int
c_exc_runenv(char *prog, char **argv, char **envp)
{
	CArr   e, f;
	usize  n;
	char **pv;
	char  *path, *s;
	char   buf[C_PATHMAX];

	c_mem_set(&e, sizeof(e), 0);

	if (c_dyn_cat(&e, newenv.p, newenv.n, sizeof(uchar)) < 0)
		return -1;

	if (envp)
		for (pv = envp; *pv; pv++)
			if (c_dyn_cat(&e, &*pv, 1, sizeof(*pv)) < 0)
				return -1;

	n = (char *)c_mem_chr(prog, C_USIZEMAX, 0)-prog;
	if ((path = c_mem_chr(prog, n, '/')))
		return c_sys_exec(prog, argv, (char **)c_arr_bget(&e, 0));

	if (!(path = c_sys_getenv("PATH")))
		path = "/bin:/usr/bin:.";

	s = path;
	c_arr_init(&f, buf, sizeof(buf));

	for (;;) {
		n = (char *)c_mem_chr(s, C_USIZEMAX, 0)-s;
		if ((s = c_mem_chr(s, n, ':')))
			*s++ = 0;
		if (c_arr_cats(&f, (!*path || *path == ':') ? "." : path) < 0)
			return -1;
		if (c_arr_cats(&f, "/")  < 0)
			return -1;
		if (c_arr_cats(&f, prog) < 0)
			return -1;
		c_sys_exec(c_arr_bget(&f, 0), argv, (char **)c_arr_bget(&e, 0));
		if (!(errno == C_ENOENT || errno == C_EACCES ||\
		    errno == C_EPERM    || errno == C_EISDIR))
			break;
		if (!(path = s))
			break;
		c_arr_trunc(&f, 0, sizeof(uchar));
	}

	c_dyn_free(&e);
	return -1;
}
