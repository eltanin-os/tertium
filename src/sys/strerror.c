#include <tertium/cpu.h>
#include <tertium/std.h>

#define S(a) (a), sizeof((a))

static struct {
	int   e;
	char *s;
	uint  n;
} errlist[] = {
	{ C_E2BIG, S("Argument list too long.") },
	{ C_EACCES, S("Permission denied.") },
	{ C_EADDRINUSE, S("Address in use.") },
	{ C_EADDRNOTAVAIL, S("Address not available.") },
	{ C_EAFNOSUPPORT, S("Address family not supported.") },
	{ C_EAGAIN, S("Resource unavailable, try again.") },
	{ C_EALREADY, S("Connection already in progress.") },
	{ C_EBADF, S("Bad file descriptor.") },
	{ C_EBADMSG, S("Bad message.") },
	{ C_EBUSY, S("Device or resource busy.") },
	{ C_ECANCELED, S("Operation canceled.") },
	{ C_ECHILD, S("No child processes.") },
	{ C_ECONNABORTED, S("Connection aborted.") },
	{ C_ECONNREFUSED, S("Connection refused.") },
	{ C_ECONNRESET, S("Connection reset.") },
	{ C_EDEADLK, S("Resource deadlock would occur.") },
	{ C_EDESTADDRREQ, S("Destination address required.") },
	{ C_EDOM, S("Mathematics argument out of domain of function.") },
	{ C_EDQUOT, S("Reserved.") },
	{ C_EEXIST, S("File exists.") },
	{ C_EFAULT, S("Bad address.") },
	{ C_EFBIG, S("File too large.") },
	{ C_EHOSTUNREACH, S("Host is unreachable.") },
	{ C_EIDRM, S("Identifier removed.") },
	{ C_EILSEQ, S("Illegal byte sequence.") },
	{ C_EINPROGRESS, S("Operation in progress.") },
	{ C_EINTR, S("Interrupted function.") },
	{ C_EINVAL, S("Invalid argument.") },
	{ C_EIO, S("I/O error.") },
	{ C_EISCONN, S("Socket is connected.") },
	{ C_EISDIR, S("Is a directory.") },
	{ C_ELOOP, S("Too many levels of symbolic links.") },
	{ C_EMFILE, S("File descriptor value too large.") },
	{ C_EMLINK, S("Too many links.") },
	{ C_EMSGSIZE, S("Message too large.") },
	{ C_EMULTIHOP, S("Reserved.") },
	{ C_ENAMETOOLONG, S("Filename too long.") },
	{ C_ENETDOWN, S("Network is down.") },
	{ C_ENETRESET, S("Connection aborted by network.") },
	{ C_ENETUNREACH, S("Network unreachable.") },
	{ C_ENFILE, S("Too many files open in system.") },
	{ C_ENOBUFS, S("No buffer space available.") },
	{ C_ENODEV, S("No such device.") },
	{ C_ENOENT, S("No such file or directory.") },
	{ C_ENOEXEC, S("Executable file format error.") },
	{ C_ENOLCK, S("No locks available.") },
	{ C_ENOLINK, S("Reserved.") },
	{ C_ENOMEM, S("Not enough space.") },
	{ C_ENOMSG, S("No message of the desired type.") },
	{ C_ENOPROTOOPT, S("Protocol not available.") },
	{ C_ENOSPC, S("No space left on device.") },
	{ C_ENOSYS, S("Functionality not supported.") },
	{ C_ENOTCONN, S("The socket is not connected.") },
	{ C_ENOTDIR, S("Not a directory or a symbolic link to a directory.") },
	{ C_ENOTEMPTY, S("Directory not empty.") },
	{ C_ENOTRECOVERABLE, S("State not recoverable.") },
	{ C_ENOTSOCK, S("Not a socket.") },
	{ C_ENOTSUP, S("Not supported.") },
	{ C_ENOTTY, S("Inappropriate I/O control operation.") },
	{ C_ENXIO, S("No such device or address.") },
	{ C_EOPNOTSUPP, S("Operation not supported on socket.") },
	{ C_EOVERFLOW, S("Value too large to be stored in data type.") },
	{ C_EOWNERDEAD, S("Previous owner died.") },
	{ C_EPERM, S("Operation not permitted.") },
	{ C_EPIPE, S("Broken pipe.") },
	{ C_EPROTO, S("Protocol error.") },
	{ C_EPROTONOSUPPORT, S("Protocol not supported.") },
	{ C_EPROTOTYPE, S("Protocol wrong type for socket.") },
	{ C_ERANGE, S("Result too large.") },
	{ C_EROFS, S("Read-only file system.") },
	{ C_ESPIPE, S("Invalid seek.") },
	{ C_ESRCH, S("No such process.") },
	{ C_ESTALE, S("Reserved.") },
	{ C_ETIMEDOUT, S("Connection timed out.") },
	{ C_ETXTBSY, S("Text file busy.") },
	{ C_EWOULDBLOCK, S("Operation would block.") },
	{ C_EXDEV, S("Cross-device link.") },
};

char *
c_sys_strerror(int e, char *s, usize n)
{
	int i;

	*s = 0;

	if (!e)
		return nil;

	for (i = 0; i < C_NELEM(errlist); i++)
		if (errno == errlist[i].e) {
			c_mem_cpy(s, C_MIN(n, errlist[i].n), errlist[i].s);
			break;
		}

	return s;
}
