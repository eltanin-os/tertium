#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[C_ERRSIZ];
static CArr arr = c_arr_INIT(buf);
static CIoq ioq = c_ioq_INIT(2, &arr, &c_sys_write);
CIoq *ioq2 = &ioq;
