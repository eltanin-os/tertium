#include "tertium/os.h"

#define nil ((void *)0)

/* errno */
#define C_E2BIG           7
#define C_EACCES          13
#define C_EADDRINUSE      98
#define C_EADDRNOTAVAIL   99
#define C_EAFNOSUPPORT    97
#define C_EAGAIN          11
#define C_EALREADY        114
#define C_EBADF           9
#define C_EBADMSG         74
#define C_EBUSY           16
#define C_ECANCELED       125
#define C_ECHILD          10
#define C_ECONNABORTED    103
#define C_ECONNREFUSED    111
#define C_ECONNRESET      104
#define C_EDEADLK         35
#define C_EDESTADDRREQ    89
#define C_EDOM            33
#define C_EDQUOT          122
#define C_EEXIST          17
#define C_EFAULT          14
#define C_EFBIG           27
#define C_EHOSTUNREACH    113
#define C_EIDRM           43
#define C_EILSEQ          84
#define C_EINPROGRESS     115
#define C_EINTR           4
#define C_EINVAL          22
#define C_EIO             5
#define C_EISCONN         106
#define C_EISDIR          21
#define C_ELOOP           40
#define C_EMFILE          24
#define C_EMLINK          31
#define C_EMSGSIZE        90
#define C_EMULTIHOP       72
#define C_ENAMETOOLONG    36
#define C_ENETDOWN        100
#define C_ENETRESET       102
#define C_ENETUNREACH     101
#define C_ENFILE          23
#define C_ENOBUFS         105
#define C_ENODEV          19
#define C_ENOENT          2
#define C_ENOEXEC         8
#define C_ENOLCK          37
#define C_ENOLINK         67
#define C_ENOMEM          12
#define C_ENOMSG          42
#define C_ENOPROTOOPT     92
#define C_ENOSPC          28
#define C_ENOSYS          38
#define C_ENOTCONN        107
#define C_ENOTDIR         20
#define C_ENOTEMPTY       39
#define C_ENOTRECOVERABLE 131
#define C_ENOTSOCK        88
#define C_ENOTSUP         95
#define C_ENOTTY          25
#define C_ENXIO           6
#define C_EOPNOTSUPP      95
#define C_EOVERFLOW       75
#define C_EOWNERDEAD      130
#define C_EPERM           1
#define C_EPIPE           32
#define C_EPROTO          71
#define C_EPROTONOSUPPORT 93
#define C_EPROTOTYPE      91
#define C_ERANGE          34
#define C_EROFS           30
#define C_ESPIPE          29
#define C_ESRCH           3
#define C_ESTALE          116
#define C_ETIMEDOUT       110
#define C_ETXTBSY         26
#define C_EWOULDBLOCK     11
#define C_EXDEV           18
#define C_ECSTM           0x66D7C8BA

/* options macros */
#define C_OAPPEND 0x00400
#define C_OCREATE 0x00040
#define C_OTRUNC  0x00200
#define C_OCEXEC  0x80000
#define C_OEXCL   0x00080

/* others macros */
#define MAP_ANON 0x20

/* syscalls macros */
#define SYS_read          0
#define SYS_write         1
#define SYS_open          2
#define SYS_close         3
#define SYS_fstat         5
#define SYS_lseek         8
#define SYS_mmap          9
#define SYS_munmap        11
#define SYS_brk           12
#define SYS_dup2          33
#define SYS_execve        59
#define SYS_exit          60
#define SYS_getcwd        79
#define SYS_chdir         80
#define SYS_fchdir        81
#define SYS_mkdir         83
#define SYS_rmdir         84
#define SYS_link          86
#define SYS_unlink        87
#define SYS_symlink       88
#define SYS_readlink      89
#define SYS_chown         92
#define SYS_fchown        92
#define SYS_getuid        102
#define SYS_getgid        104
#define SYS_mknod         133
#define SYS_getdents      217
#define SYS_clock_gettime 228
#define SYS_fstatat       262
#define SYS_linkat        265

/* variadic macros */
#define va_arg(a, b)   __builtin_va_arg(a, b)
#define va_copy(a, b)  __builtin_va_copy(a, b)
#define va_end(a)      __builtin_va_end(a)
#define va_start(a, b) __builtin_va_start(a, b)

/* types */
typedef unsigned short     ushort;
typedef unsigned char      uchar;
typedef unsigned long      ulong;
typedef unsigned int       uint;
typedef long long          vlong;
typedef unsigned long long uvlong;
typedef long long          intptr;
typedef unsigned long long uintptr;
typedef unsigned long      usize;
typedef long               size;
typedef unsigned           Rune;
typedef unsigned char      u8int;
typedef unsigned short     u16int;
typedef unsigned           u32int;
typedef unsigned long long u64int;
typedef char               s8int;
typedef short              s16int;
typedef int                s32int;
typedef long long          s64int;

//typedef char * va_list;
typedef __builtin_va_list va_list;

/* fallback types */
typedef struct {
	long   d_ino;
	vlong  d_off;
	u16int d_reclen;
	uchar  d_type;
	char   d_name[256];
} __fb_dirent;

typedef struct {
	ulong  st_dev;
	ulong  st_ino;
	ulong  st_nlink;
	u32int st_mode;
	u32int st_uid;
	u32int st_gid;
	u32int __pad0;
	ulong  st_rdev;
	ulong  st_size;
	ulong  st_blksize;
	ulong  st_blocks;
	vlong  st_atime;
	ulong  st_atime_nsec;
	vlong  st_mtime;
	ulong  st_mtime_nsec;
	vlong  st_ctime;
	ulong  st_ctime_nsec;
	long   __unused[3];
} __fb_stat;

typedef struct {
	vlong tv_sec;
	long  tv_nsec;
} __fb_time;
