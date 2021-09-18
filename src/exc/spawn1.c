#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_id
c_exc_spawn1(char *prog, char **argv, char **envp, ctype_fd *fd, int to)
{
	ctype_fd sync[2];
	ctype_fd pipe[2];
	ctype_error sverr;
	ctype_id id;

	if (c_nix_pipe(pipe) < 0)
		return 0;
	if (c_nix_fdset(pipe[0], C_OCEXEC) < 0 ||
	    c_nix_pipe2(sync, C_OCEXEC) < 0) {
		c_nix_fdclose(pipe[0]);
		c_nix_fdclose(pipe[1]);
		return 0;
	}
	if ((id = c_nix_fork()) < 0) {
		c_nix_fdclose(sync[0]);
		c_nix_fdclose(sync[1]);
		c_nix_fdclose(pipe[0]);
		c_nix_fdclose(pipe[1]);
		return 0;
	}
	if (!id) {
		c_nix_fdclose(sync[0]);
		c_nix_fdclose(pipe[!to]);
		c_nix_fdmove(to, pipe[to]);
		c_exc_runenv(prog, argv, envp);
		sverr = errno;
		c_nix_fdwrite(sync[1], &sverr, sizeof(sverr));
		c_std_exit(127);
	}
	c_nix_fdclose(pipe[to]);
	c_nix_fdclose(sync[1]);
	sync[1] = c_nix_fdread(sync[0], &sverr, sizeof(sverr));
	c_nix_fdclose(sync[0]);
	if (sync[1]) {
		c_nix_fdclose(pipe[!to]);
		c_nix_waitpid(id, nil, 0);
		errno = sverr;
		return 0;
	}
	*fd = pipe[!to];
	return id;
}
