#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[C_BIOSIZ];
static ctype_ioq ioq = c_ioq_INIT(1, buf, &c_sys_write);
ctype_ioq *ioq1 = &ioq;
