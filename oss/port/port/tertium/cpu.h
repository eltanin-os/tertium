#define _GNU_SOURCE

/* freestanding environment */
#include <sys/types.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "tertium/os.h"

#define nil ((void *)0)

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef long long vlong;
typedef unsigned long long uvlong;
typedef long long intptr;
typedef unsigned long long uintptr;
typedef size_t usize;
typedef ssize_t size;
typedef int32_t Rune;
typedef uint8_t u8int;
typedef uint16_t u16int;
typedef uint32_t u32int;
typedef uint64_t u64int;
typedef int8_t s8int;
typedef int16_t s16int;
typedef int32_t s32int;
typedef int64_t s64int;
