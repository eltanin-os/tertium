#include <tertium/cpu.h>
#include <tertium/std.h>

#define NEXTCOLON(a, b) \
{ if (!((a) = c_str_chr((b), -1, ':'))) (a) = c_str_chr((b), -1, '\0'); }
#define DEFPATH "/bin:/usr/bin:."

extern ctype_arr _tertium_exc_env;

static ctype_status
copyto(ctype_arr *dest, char **envp)
{
	char **args;
	usize len;

	len = 0;
	for (args = envp; *args; ++args) ++len;
	if (c_dyn_ready(dest, len, sizeof(char *)) < 0) return -1;
	(void)c_arr_get(dest, len - 1, sizeof(char **));

	args = c_arr_data(dest);
	while (*envp) *args++ = *envp++;
	return 0;
}

static ctype_status
merge(ctype_arr *dest, ctype_arr *s)
{
	usize len, pos;
	char **args, **sp;
	void *tmp;

	len = c_arr_len(s, sizeof(char *));
	if (!len) return 0;
	c_dyn_ready(dest, len, sizeof(char *));

	sp = c_arr_data(s);
	for (; *sp; ++sp) {
		len = c_str_cspn(*sp, -1, "=");
		for (args = c_arr_data(dest); *args; ++args) {
			if (c_str_cspn(*args, -1, "=") - len) continue;
			if (c_mem_cmp(*args, len, *sp)) continue;
			if ((*sp)[len] == '=') {
				*args = *sp;
				goto next;
			} else {
				pos = c_arr_len(dest, sizeof(char *)) - 1;
				tmp = c_arr_get(dest, pos, sizeof(char *));
				*args = *(char **)tmp;
				c_arr_trunc(dest, pos, sizeof(char *));
				goto next;
			}
		}
		c_arr_cat(dest, &*sp, 1, sizeof(char *));
next:
		;
	}
	return 0;
}

ctype_status
c_exc_runenv(char *prog, char **argv, char **envp)
{
	ctype_arr e, f;
	ctype_error sverr;
	usize off;
	char *path, *s;
	char buf[C_LIM_PATHMAX];

	c_mem_set(&e, sizeof(e), 0);
	if (copyto(&e, envp) < 0) return -1;
	if (merge(&e, &_tertium_exc_env) < 0) return -1;

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
