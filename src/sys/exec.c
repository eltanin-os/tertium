#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_exec(char *path, char **argv, char **envp)
{
	return c_sys_call(__NR_execve, path, argv, envp);
}
