#define _GNU_SOURCE

/* nix/std environment */
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#undef st_atime
#undef st_mtime
#undef st_ctime
#undef offsetof

#define c_sys_call syscall

/* use sysconf as fallback, as the posix minimum is a bad option ("1") */
#ifndef PAGESIZE
#define PAGESIZE sysconf(_SC_PAGESIZE)
#endif

/* limits macros */
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

typedef struct stat __fb_stat;
typedef struct timespec __fb_time;
