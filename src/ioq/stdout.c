#include <tertium/cpu.h>
#include <tertium/std.h>

static uchar buf[C_IOQ_BSIZ];
static ctype_ioq ioq = c_ioq_INIT(1, buf, &c_nix_fdwrite);
ctype_ioq *ioq1 = &ioq;
