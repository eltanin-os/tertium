#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[IOQBUFSIZ];
static Membuf arr = c_arr_INIT(buf);
static Ioq ioq = c_ioq_INIT(0, &arr, &c_sys_read);
Ioq *ioq0 = &ioq;
