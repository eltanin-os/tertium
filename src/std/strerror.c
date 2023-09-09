#include <tertium/cpu.h>
#include <tertium/std.h>

#define S(a) (a), sizeof((a))

static struct {
	int e;
	char *s;
	uint n;
} errlist[] = {
	{ C_ERR_E2BIG, S("Argument list too long") },
	{ C_ERR_EACCES, S("Permission denied") },
	{ C_ERR_EADDRINUSE, S("Address in use") },
	{ C_ERR_EADDRNOTAVAIL, S("Address not available") },
	{ C_ERR_EAFNOSUPPORT, S("Address family not supported") },
	{ C_ERR_EAGAIN, S("Resource unavailable, try again") },
	{ C_ERR_EALREADY, S("Connection already in progress") },
	{ C_ERR_EBADF, S("Bad file descriptor") },
	{ C_ERR_EBADMSG, S("Bad message") },
	{ C_ERR_EBUSY, S("Device or resource busy") },
	{ C_ERR_ECANCELED, S("Operation canceled") },
	{ C_ERR_ECHILD, S("No child processes") },
	{ C_ERR_ECONNABORTED, S("Connection aborted") },
	{ C_ERR_ECONNREFUSED, S("Connection refused") },
	{ C_ERR_ECONNRESET, S("Connection reset") },
	{ C_ERR_EDEADLK, S("Resource deadlock would occur") },
	{ C_ERR_EDESTADDRREQ, S("Destination address required") },
	{ C_ERR_EDOM, S("Mathematics argument out of domain of function") },
	{ C_ERR_EDQUOT, S("Reserved") },
	{ C_ERR_EEXIST, S("File exists") },
	{ C_ERR_EFAULT, S("Bad address") },
	{ C_ERR_EFBIG, S("File too large") },
	{ C_ERR_EHOSTUNREACH, S("Host is unreachable") },
	{ C_ERR_EIDRM, S("Identifier removed") },
	{ C_ERR_EILSEQ, S("Illegal byte sequence") },
	{ C_ERR_EINPROGRESS, S("Operation in progress") },
	{ C_ERR_EINTR, S("Interrupted function") },
	{ C_ERR_EINVAL, S("Invalid argument") },
	{ C_ERR_EIO, S("I/O error") },
	{ C_ERR_EISCONN, S("Socket is connected") },
	{ C_ERR_EISDIR, S("Is a directory") },
	{ C_ERR_ELOOP, S("Too many levels of symbolic links") },
	{ C_ERR_EMFILE, S("File descriptor value too large") },
	{ C_ERR_EMLINK, S("Too many links") },
	{ C_ERR_EMSGSIZE, S("Message too large") },
	{ C_ERR_EMULTIHOP, S("Reserved") },
	{ C_ERR_ENAMETOOLONG, S("Filename too long") },
	{ C_ERR_ENETDOWN, S("Network is down") },
	{ C_ERR_ENETRESET, S("Connection aborted by network") },
	{ C_ERR_ENETUNREACH, S("Network unreachable") },
	{ C_ERR_ENFILE, S("Too many files open in system") },
	{ C_ERR_ENOBUFS, S("No buffer space available") },
	{ C_ERR_ENODEV, S("No such device") },
	{ C_ERR_ENOENT, S("No such file or directory") },
	{ C_ERR_ENOEXEC, S("Executable file format error") },
	{ C_ERR_ENOLCK, S("No locks available") },
	{ C_ERR_ENOLINK, S("Reserved") },
	{ C_ERR_ENOMEM, S("Not enough space") },
	{ C_ERR_ENOMSG, S("No message of the desired type") },
	{ C_ERR_ENOPROTOOPT, S("Protocol not available") },
	{ C_ERR_ENOSPC, S("No space left on device") },
	{ C_ERR_ENOSYS, S("Functionality not supported") },
	{ C_ERR_ENOTCONN, S("The socket is not connected") },
	{ C_ERR_ENOTDIR, S("Not a directory or a symbolic link to a directory") },
	{ C_ERR_ENOTEMPTY, S("Directory not empty") },
	{ C_ERR_ENOTRECOVERABLE, S("State not recoverable") },
	{ C_ERR_ENOTSOCK, S("Not a socket") },
	{ C_ERR_ENOTSUP, S("Not supported") },
	{ C_ERR_ENOTTY, S("Inappropriate I/O control operation") },
	{ C_ERR_ENXIO, S("No such device or address") },
	{ C_ERR_EOPNOTSUPP, S("Operation not supported on socket") },
	{ C_ERR_EOVERFLOW, S("Value too large to be stored in data type") },
	{ C_ERR_EOWNERDEAD, S("Previous owner died") },
	{ C_ERR_EPERM, S("Operation not permitted") },
	{ C_ERR_EPIPE, S("Broken pipe") },
	{ C_ERR_EPROTO, S("Protocol error") },
	{ C_ERR_EPROTONOSUPPORT, S("Protocol not supported") },
	{ C_ERR_EPROTOTYPE, S("Protocol wrong type for socket") },
	{ C_ERR_ERANGE, S("Result too large") },
	{ C_ERR_EROFS, S("Read-only file system") },
	{ C_ERR_ESPIPE, S("Invalid seek") },
	{ C_ERR_ESRCH, S("No such process") },
	{ C_ERR_ESTALE, S("Reserved") },
	{ C_ERR_ETIMEDOUT, S("Connection timed out") },
	{ C_ERR_ETXTBSY, S("Text file busy") },
	{ C_ERR_EWOULDBLOCK, S("Operation would block") },
	{ C_ERR_EXDEV, S("Cross-device link") },
};

char *
c_std_strerror(int e, char *s, usize n)
{
	int i;

	*s = 0;
	if (!e) return nil;

	for (i = 0; i < (int)C_STD_NELEM(errlist); ++i) {
		if (e == errlist[i].e) {
			c_mem_cpy(s, errlist[i].s, C_STD_MIN(n, errlist[i].n));
			break;
		}
	}
	return s;
}
