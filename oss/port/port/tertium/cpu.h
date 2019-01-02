#define _GNU_SOURCE

/* freestanding environment */
#include <sys/types.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* nix/std environment */
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define c_sys_call syscall

#undef st_atime
#undef st_mtime
#undef st_ctime
#undef offsetof

#define USIZE_MAX SIZE_MAX
#undef  SIZE_MAX
#define SIZE_MAX  SSIZE_MAX

#ifndef ARG_MAX
#define ARG_MAX 4096
#endif

#ifndef CHILD_MAX
#define CHILD_MAX 25
#endif

#ifndef OPEN_MAX
#define OPEN_MAX 20
#endif

#ifndef PAGESIZE
#define PAGESIZE getpagesize();
#endif

#ifndef SYMLOOP_MAX
#define SYMLOOP_MAX 8
#endif

#define nil ((void *)0)

typedef struct stat __fb_stat;

typedef unsigned short     ushort;
typedef unsigned char      uchar;
typedef unsigned long      ulong;
typedef unsigned int       uint;
typedef long long          vlong;
typedef unsigned long long uvlong;
typedef long long          intptr;
typedef unsigned long long uintptr;
typedef size_t             usize;
typedef ssize_t            size;
typedef int32_t            Rune;
typedef uint8_t            u8int;
typedef uint16_t           u16int;
typedef uint32_t           u32int;
typedef uint64_t           u64int;
typedef int8_t             s8int;
typedef int16_t            s16int;
typedef int32_t            s32int;
typedef int64_t            s64int;
