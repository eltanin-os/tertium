#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[C_BIOSIZ];
static CArr arr = c_arr_INIT(buf);
static CIoq ioq = c_ioq_INIT(1, &arr, &c_sys_write);
CIoq *ioq1 = &ioq;
