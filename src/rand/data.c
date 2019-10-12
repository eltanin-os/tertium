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
	int i, j;

	for (i = 0; i < 12; ++i)
		t[i] = s[i] ^ seed[12 + i];
	for (i = 0; i < 8; ++i)
		d[i] = seed[24 + i];

	x = t[11];
	sum = 0;

	for (i = 0; i < 16; ++i) {
		sum += 0x9E3779B9;
		for (j = 0; j < (int)C_NELEM(tab); j++)
			MUSH(tab[j].x, tab[j].y);
	}

	for (i = 0; i < 8; ++i)
		d[i] ^= t[i + 4];

	for (i = 0; i < 16; ++i) {
		sum += 0x9E3779B9;
		for (j = 0; j < (int)C_NELEM(tab); j++)
			MUSH(tab[j].x, tab[j].y);
	}

	for (i = 0; i < 8; ++i)
		d[i] ^= t[i + 4];
}

char *
c_rand_data(char *s, usize n)
{
	u32int buf[12], tmp[8];
	uint r;

	if (!haveseed) {
		c_rand_genseed(seedbuf, sizeof(seedbuf));
		++haveseed;
	}

	c_rand_genseed((void *)(uintptr)buf, sizeof(buf));
	while (n) {
		r = C_MIN(n, 64);
		++buf[0], ++buf[5], ++buf[11];
		surf(tmp, buf, (void *)seedbuf);
		c_mem_cpy(s, r, tmp);
		s += r;
		n -= r;
	}
	return s;
}
