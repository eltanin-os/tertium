#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[IOQBUFSIZ];
static Membuf arr = c_arr_INIT(buf);
static Ioq ioq = c_ioq_INIT(1, &arr, &c_sys_write);
Ioq *ioq1 = &ioq;
