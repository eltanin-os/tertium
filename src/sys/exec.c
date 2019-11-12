#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_sys_exec(char *path, char **argv, char **envp)
{
	return c_std_syscall(SYS_execve, path, argv, envp);
}
