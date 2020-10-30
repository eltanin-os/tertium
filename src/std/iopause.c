#include <tertium/cpu.h>
#include <tertium/std.h>

ctype_status
c_std_iopause(ctype_iopause *p, uint n, ctype_taia *deadline, ctype_taia *stamp)
{
	ctype_taia t;
	int millisecs;
	double d;
	uint i;

	if (c_taia_less(deadline, stamp)) {
		millisecs = 0;
	} else {
		t = *stamp;
		c_taia_sub(&t, deadline, &t);
		if ((d = c_taia_approx(&t)) > 1000.0)
			d = 1000.0;
		millisecs = d * 1000.0 + 20.0;
	}

	for (i = 0; i < n; ++i)
		p[i].revents = 0;

	return c_sys_poll(p, n, millisecs);
}
