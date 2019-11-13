#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[C_BIOSIZ];
static ctype_ioq ioq = c_ioq_INIT(0, buf, &c_sys_read);
ctype_ioq *ioq0 = &ioq;
