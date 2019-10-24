#include <tertium/cpu.h>
#include <tertium/std.h>

#define ROT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define MUSH(a, b) x = t[(a)] += (((x ^ seed[(a)]) + sum) ^ ROT(x, (b)))

struct {
	int x;
	int y;
} tab[] = {
	{ 0, 5 }, { 1, 7 }, { 2,  9 }, { 3,  13 },
	{ 4, 5 }, { 5, 7 }, { 6,  9 }, { 7,  13 },
	{ 8, 5 }, { 9, 7 }, { 10, 9 }, { 11, 13 },
};

static char seedbuf[256];
static int haveseed;

void
surf(u32int *d, u32int *s, u32int *seed)
{
	u32int t[12];
	u32int x, sum;
	int i, j, k;

	for (i = 0; i < 12; ++i)
		t[i] = s[i] ^ seed[12 + i];
	for (i = 0; i < 8; ++i)
		d[i] = seed[24 + i];

	x = t[11];
	sum = 0;

	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 16; ++j) {
			sum += 0x9E3779B9;
			for (k = 0; k < (int)C_NELEM(tab); k++)
				MUSH(tab[k].x, tab[k].y);
		}

		for (j = 0; j < 8; ++j)
			d[j] ^= t[j + 4];
	}

	++s[0], ++s[5], ++s[11];
}

char *
c_rand_data(char *s, usize n)
{
	u32int buf[48], tmp[32];
	uint r;

	if (!haveseed) {
		c_rand_genseed(seedbuf, sizeof(seedbuf));
		++haveseed;
	}

	c_rand_genseed((void *)(uintptr)buf, sizeof(buf));
	while (n) {
		n -= r = C_MIN(n, 32);
		surf(tmp, buf, (void *)seedbuf);
		c_mem_cpy(s + n, r, tmp);
	}

	return s;
}
