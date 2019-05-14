#define _GNU_SOURCE

/* nix/std environment */
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#undef st_atime
#undef st_mtime
#undef st_ctime
#undef offsetof

#define __asm_syscall syscall

/* errno */
#define C_E2BIG E2BIG
#define C_EACCES EACCES
#define C_EADDRINUSE EADDRINUSE
#define C_EADDRNOTAVAIL EADDRNOTAVAIL
#define C_EAFNOSUPPORT EAFNOSUPPORT
#define C_EAGAIN EAGAIN
#define C_EALREADY EALREADY
#define C_EBADF EBADF
#define C_EBADMSG EBADMSG
#define C_EBUSY EBUSY
#define C_ECANCELED ECANCELED
#define C_ECHILD ECHILD
#define C_ECONNABORTED ECONNABORTED
#define C_ECONNREFUSED ECONNREFUSED
#define C_ECONNRESET ECONNRESET
#define C_EDEADLK EDEADLK
#define C_EDESTADDRREQ EDESTADDRREQ
#define C_EDOM EDOM
#define C_EDQUOT EDQUOT
#define C_EEXIST EEXIST
#define C_EFAULT EFAULT
#define C_EFBIG EFBIG
#define C_EHOSTUNREACH EHOSTUNREACH
#define C_EIDRM EIDRM
#define C_EILSEQ EILSEQ
#define C_EINPROGRESS EINPROGRESS
#define C_EINTR EINTR
#define C_EINVAL EINVAL
#define C_EIO EIO
#define C_EISCONN EISCONN
#define C_EISDIR EISDIR
#define C_ELOOP ELOOP
#define C_EMFILE EMFILE
#define C_EMLINK EMLINK
#define C_EMSGSIZE EMSGSIZE
#define C_EMULTIHOP EMULTIHOP
#define C_ENAMETOOLONG ENAMETOOLONG
#define C_ENETDOWN ENETDOWN
#define C_ENETRESET ENETRESET
#define C_ENETUNREACH ENETUNREACH
#define C_ENFILE ENFILE
#define C_ENOBUFS ENOBUFS
#define C_ENODEV ENODEV
#define C_ENOENT ENOENT
#define C_ENOEXEC ENOEXEC
#define C_ENOLCK ENOLCK
#define C_ENOLINK ENOLINK
#define C_ENOMEM ENOMEM
#define C_ENOMSG ENOMSG
#define C_ENOPROTOOPT ENOPROTOOPT
#define C_ENOSPC ENOSPC
#define C_ENOSYS ENOSYS
#define C_ENOTCONN ENOTCONN
#define C_ENOTDIR ENOTDIR
#define C_ENOTEMPTY ENOTEMPTY
#define C_ENOTRECOVERABLE ENOTRECOVERABLE
#define C_ENOTSOCK ENOTSOCK
#define C_ENOTSUP ENOTSUP
#define C_ENOTTY ENOTTY
#define C_ENXIO ENXIO
#define C_EOPNOTSUPP EOPNOTSUPP
#define C_EOVERFLOW EOVERFLOW
#define C_EOWNERDEAD EOWNERDEAD
#define C_EPERM EPERM
#define C_EPIPE EPIPE
#define C_EPROTO EPROTO
#define C_EPROTONOSUPPORT EPROTONOSUPPORT
#define C_EPROTOTYPE EPROTOTYPE
#define C_ERANGE ERANGE
#define C_EROFS EROFS
#define C_ESPIPE ESPIPE
#define C_ESRCH ESRCH
#define C_ESTALE ESTALE
#define C_ETIMEDOUT ETIMEDOUT
#define C_ETXTBSY ETXTBSY
#define C_EWOULDBLOCK EWOULDBLOCK
#define C_EXDEV EXDEV
#define C_ECSTM 0x66D7C8BA

/* use sysconf as fallback, as the posix minimum is a bad option ("1") */
#ifndef PAGESIZE
#define PAGESIZE sysconf(_SC_PAGESIZE)
#endif

/* limits macros */
#define C_NAMEMAX 255
#define C_PATHMAX 1024

#define C_ARGMAX       4096
#define C_CHILDMAX     25
#define C_HOSTNAMEMAX  255
#define C_LOGINNAMEMAX 9
#define C_NGROUPSMAX   8
#define C_OPENMAX      20
#define C_PAGESIZE     PAGESIZE
#define C_SYMLOOPMAX   8
#define C_TTYNAMEMAX   9

#define C_CHARBIT   8
#define C_CHARMAX   0x7F
#define C_UCHARMAX  0xFF
#define C_INTMAX    0x7FFFFFFF
#define C_UINTMAX   0xFFFFFFFFU
#define C_LONGMAX   0x7FFFFFFFL
#define C_ULONGMAX  0xFFFFFFFFUL
#define C_SHRTMAX   0x7FFF
#define C_USHRTMAX  0xFFFFU
#define C_SIZEMAX   0x7FFF
#define C_USIZEMAX  0xFFFFU
#define C_VLONGMAX  0x7FFFFFFFFFFFFFFFLL
#define C_UVLONGMAX 0x7FFFFFFFFFFFFFFFULL
#define C_CHARMIN   (-C_CHARMAX-1)
#define C_INTMIN    (-C_INTMAX-1)
#define C_LONGMIN   (-C_LONGMAX-1)
#define C_SHRTMIN   (-C_SHRTMAX-1)
#define C_SIZEMIN   (-C_SIZEMAX-1)
#define C_VLONGMIN  (-C_VLONGMAX-1)

/* options macros */
#define C_OREAD  O_RDONLY
#define C_OWRITE O_WRONLY
#define C_ORDWR  O_RDWR
#define C_OTRUNC O_TRUNC
#define C_OCEXEC O_CLOEXEC
#define C_OEXCL  O_EXCL

/* stat macros */
#define C_IFMT  S_IFMT
#define C_IFBLK S_IFBLK
#define C_IFCHR S_IFCHR
#define C_IFDIR S_IFDIR
#define C_IFIFO S_IFIFO
#define C_IFLNK S_IFLNK
#define C_IFREG S_IFREG
#define C_IFSCK S_IFSOCK

#define C_ISBLK(a)  S_ISBLK(a)
#define C_ISCHR(a)  S_ISCHR(a)
#define C_ISDIR(a)  S_ISDIR(a)
#define C_ISFIFO(a) S_ISFIFO(a)
#define C_ISLNK(a)  S_ISLNK(a)
#define C_ISREG(a)  S_ISREG(a)
#define C_ISSCK(a)  S_ISSOCK(a)

#define C_ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO)
#define C_ALLPERMS    (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
#define C_DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

typedef struct dirent   __fb_dirent;
typedef struct stat     __fb_stat;
typedef struct timespec __fb_time;