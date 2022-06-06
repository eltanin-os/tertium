#include <tertium/cpu.h>
#include <tertium/std.h>

#define NEXTCOLON(a, b) \
{ if (!((a) = c_str_chr((b), -1, ':'))) (a) = c_str_chr((b), -1, '\0'); }
#define DEFPATH "/bin:/usr/bin:."

extern ctype_arr _tertium_exc_env;

ctype_status
c_exc_runenv(char *prog, char **argv, char **envp)
{
	ctype_arr e, f;
	ctype_error sverr;
	usize off;
	char *path, *s;
	char buf[C_LIM_PATHMAX];

	c_mem_set(&e, sizeof(e), 0);
	for (; envp && *envp; ++envp)
		if (c_dyn_cat(&e, &*envp, 1, sizeof(*envp)) < 0) return -1;

	if (c_dyn_tofrom(&e, &_tertium_exc_env) < 0) return -1;

	s = nil;
	if (c_dyn_cat(&e, &s, 1, sizeof(void *)) < 0) return -1;

	if ((path = c_str_chr(prog, -1, '/')))
		return c_sys_execve(prog, argv, (char **)c_arr_data(&e));

	if (!(path = c_std_getenv("PATH"))) path = DEFPATH;

	sverr = 0;
	c_arr_init(&f, buf, sizeof(buf));
	while (path) {
		NEXTCOLON(s, path);
		off = s - path;
		c_arr_trunc(&f, 0, sizeof(uchar));
		if (c_arr_fmt(&f, "%.*s/%s", off, path, prog) < 0) {
			if (errno == C_ERR_ENOMEM) errno = C_ERR_ENAMETOOLONG;
			break;
		}
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
	if (sverr) errno = sverr;
	c_dyn_free(&e);
	return -1;
}
