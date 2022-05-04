#include <tertium/cpu.h>
#include <tertium/std.h>

extern ctype_arr __exc_env;

ctype_status
c_exc_runenv(char *prog, char **argv, char **envp)
{
	ctype_arr e, f;
	ctype_error sverr;
	usize off;
	char *path, *s;
	char buf[C_LIM_PATHMAX];

	c_mem_set(&e, sizeof(e), 0);
	if (c_dyn_cat(&e, __exc_env.p, __exc_env.n, sizeof(uchar)) < 0)
		return -1;

	if (envp)
		for (; *envp; ++envp)
			if (c_dyn_cat(&e, &*envp, 1, sizeof(*envp)) < 0)
				return -1;

	if (e.n)
		c_mem_set(e.p + e.n, sizeof(void *), 0);

	if ((path = c_str_chr(prog, -1, '/')))
		return c_sys_execve(prog, argv, (char **)c_arr_data(&e));

	if (!(path = c_std_getenv("PATH")))
		path = "/bin:/usr/bin:.";

	sverr = 0;
	s = path;
	c_arr_init(&f, buf, sizeof(buf));
	while (s) {
		c_arr_trunc(&f, 0, sizeof(uchar));
		off = (s = c_str_chr(path, -1, ':')) ? s - path : -1;
		if (c_arr_fmt(&f, "%.*s/%s", off, path, prog) < 0)
			return -1;
		c_sys_execve(c_arr_data(&f), argv, (char **)c_arr_data(&e));
		if (errno != C_ERR_ENOENT) {
			sverr = errno;
			if (!(errno == C_ERR_EACCES ||
			    errno == C_ERR_EPERM ||
			    errno == C_ERR_EISDIR))
				break;
		}
		path += off + 1;
	}

	if (sverr)
		errno = sverr;

	c_dyn_free(&e);
	return -1;
}
