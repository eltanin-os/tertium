#include <tertium/cpu.h>
#include <tertium/std.h>

size
c_nix_fdcat(ctype_fd dest, ctype_fd src)
{
	size in, out;
	char buf[C_BIOSIZ];

	out = 0;
	while ((in = c_nix_fdread(src, buf, sizeof(buf))) > 0) {
		if (c_nix_allrw(c_nix_fdwrite, dest, buf, in) < 0)
			return -2;
		out += in;
	}
	return in ? -1 : out;
}
