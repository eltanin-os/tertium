#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_exc_spawn0(char *prog, char **argv, char **envp)
{
	ctype_fd sync[2];
	ctype_error sverr;
	ctype_id id;

	if (c_sys_pipecoe(sync) < 0)
		return 0;
	if ((id = c_sys_fork()) < 0) {
		c_sys_close(sync[0]);
		c_sys_close(sync[1]);
		return 0;
	}
	if (!id) {
		c_sys_close(sync[0]);
		c_exc_runenv(prog, argv, envp);
		sverr = errno;
		c_sys_write(sync[1], &sverr, sizeof(sverr));
		c_std_exit(127);
	}
	c_sys_close(sync[1]);
	sync[1] = c_sys_read(sync[0], &sverr, sizeof(sverr));
	c_sys_close(sync[0]);
	if (sync[1] == sizeof(sverr)) {
		c_sys_waitpid(id, nil, 0);
		errno = sverr;
		return 0;
	}
	return id;
}
