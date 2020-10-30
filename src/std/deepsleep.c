#include <tertium/cpu.h>
#include <tertium/std.h>

void
c_std_deepsleep(ctype_taia *deadline, ctype_taia *stamp)
{
	ctype_iopause x;

	while (c_taia_less(stamp, deadline)) {
		c_std_iopause(&x, 0, deadline, stamp);
		if (stamp)
			c_taia_now(stamp);
	}
}
