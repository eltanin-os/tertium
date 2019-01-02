#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[ERRBUFSIZ];
static Membuf arr = c_arr_INIT(buf);
static Ioq ioq = c_ioq_INIT(2, &arr, &c_sys_write);
Ioq *ioq2 = &ioq;
