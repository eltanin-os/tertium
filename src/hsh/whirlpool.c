#include <tertium/cpu.h>
#include <tertium/std.h>

#include "__int__.h"

static u64int sbox[] = {
	0x18186018c07830d8ULL, 0x23238c2305af4626ULL,
	0xc6c63fc67ef991b8ULL, 0xe8e887e8136fcdfbULL,
	0x878726874ca113cbULL, 0xb8b8dab8a9626d11ULL,
	0x0101040108050209ULL, 0x4f4f214f426e9e0dULL,
	0x3636d836adee6c9bULL, 0xa6a6a2a6590451ffULL,
	0xd2d26fd2debdb90cULL, 0xf5f5f3f5fb06f70eULL,
	0x7979f979ef80f296ULL, 0x6f6fa16f5fcede30ULL,
	0x91917e91fcef3f6dULL, 0x52525552aa07a4f8ULL,
	0x60609d6027fdc047ULL, 0xbcbccabc89766535ULL,
	0x9b9b569baccd2b37ULL, 0x8e8e028e048c018aULL,
	0xa3a3b6a371155bd2ULL, 0x0c0c300c603c186cULL,
	0x7b7bf17bff8af684ULL, 0x3535d435b5e16a80ULL,
	0x1d1d741de8693af5ULL, 0xe0e0a7e05347ddb3ULL,
	0xd7d77bd7f6acb321ULL, 0xc2c22fc25eed999cULL,
	0x2e2eb82e6d965c43ULL, 0x4b4b314b627a9629ULL,
	0xfefedffea321e15dULL, 0x575741578216aed5ULL,
	0x15155415a8412abdULL, 0x7777c1779fb6eee8ULL,
	0x3737dc37a5eb6e92ULL, 0xe5e5b3e57b56d79eULL,
	0x9f9f469f8cd92313ULL, 0xf0f0e7f0d317fd23ULL,
	0x4a4a354a6a7f9420ULL, 0xdada4fda9e95a944ULL,
	0x58587d58fa25b0a2ULL, 0xc9c903c906ca8fcfULL,
	0x2929a429558d527cULL, 0x0a0a280a5022145aULL,
	0xb1b1feb1e14f7f50ULL, 0xa0a0baa0691a5dc9ULL,
	0x6b6bb16b7fdad614ULL, 0x85852e855cab17d9ULL,
	0xbdbdcebd8173673cULL, 0x5d5d695dd234ba8fULL,
	0x1010401080502090ULL, 0xf4f4f7f4f303f507ULL,
	0xcbcb0bcb16c08bddULL, 0x3e3ef83eedc67cd3ULL,
	0x0505140528110a2dULL, 0x676781671fe6ce78ULL,
	0xe4e4b7e47353d597ULL, 0x27279c2725bb4e02ULL,
	0x4141194132588273ULL, 0x8b8b168b2c9d0ba7ULL,
	0xa7a7a6a7510153f6ULL, 0x7d7de97dcf94fab2ULL,
	0x95956e95dcfb3749ULL, 0xd8d847d88e9fad56ULL,
	0xfbfbcbfb8b30eb70ULL, 0xeeee9fee2371c1cdULL,
	0x7c7ced7cc791f8bbULL, 0x6666856617e3cc71ULL,
	0xdddd53dda68ea77bULL, 0x17175c17b84b2eafULL,
	0x4747014702468e45ULL, 0x9e9e429e84dc211aULL,
	0xcaca0fca1ec589d4ULL, 0x2d2db42d75995a58ULL,
	0xbfbfc6bf9179632eULL, 0x07071c07381b0e3fULL,
	0xadad8ead012347acULL, 0x5a5a755aea2fb4b0ULL,
	0x838336836cb51befULL, 0x3333cc3385ff66b6ULL,
	0x636391633ff2c65cULL, 0x02020802100a0412ULL,
	0xaaaa92aa39384993ULL, 0x7171d971afa8e2deULL,
	0xc8c807c80ecf8dc6ULL, 0x19196419c87d32d1ULL,
	0x494939497270923bULL, 0xd9d943d9869aaf5fULL,
	0xf2f2eff2c31df931ULL, 0xe3e3abe34b48dba8ULL,
	0x5b5b715be22ab6b9ULL, 0x88881a8834920dbcULL,
	0x9a9a529aa4c8293eULL, 0x262698262dbe4c0bULL,
	0x3232c8328dfa64bfULL, 0xb0b0fab0e94a7d59ULL,
	0xe9e983e91b6acff2ULL, 0x0f0f3c0f78331e77ULL,
	0xd5d573d5e6a6b733ULL, 0x80803a8074ba1df4ULL,
	0xbebec2be997c6127ULL, 0xcdcd13cd26de87ebULL,
	0x3434d034bde46889ULL, 0x48483d487a759032ULL,
	0xffffdbffab24e354ULL, 0x7a7af57af78ff48dULL,
	0x90907a90f4ea3d64ULL, 0x5f5f615fc23ebe9dULL,
	0x202080201da0403dULL, 0x6868bd6867d5d00fULL,
	0x1a1a681ad07234caULL, 0xaeae82ae192c41b7ULL,
	0xb4b4eab4c95e757dULL, 0x54544d549a19a8ceULL,
	0x93937693ece53b7fULL, 0x222288220daa442fULL,
	0x64648d6407e9c863ULL, 0xf1f1e3f1db12ff2aULL,
	0x7373d173bfa2e6ccULL, 0x12124812905a2482ULL,
	0x40401d403a5d807aULL, 0x0808200840281048ULL,
	0xc3c32bc356e89b95ULL, 0xecec97ec337bc5dfULL,
	0xdbdb4bdb9690ab4dULL, 0xa1a1bea1611f5fc0ULL,
	0x8d8d0e8d1c830791ULL, 0x3d3df43df5c97ac8ULL,
	0x97976697ccf1335bULL, 0x0000000000000000ULL,
	0xcfcf1bcf36d483f9ULL, 0x2b2bac2b4587566eULL,
	0x7676c57697b3ece1ULL, 0x8282328264b019e6ULL,
	0xd6d67fd6fea9b128ULL, 0x1b1b6c1bd87736c3ULL,
	0xb5b5eeb5c15b7774ULL, 0xafaf86af112943beULL,
	0x6a6ab56a77dfd41dULL, 0x50505d50ba0da0eaULL,
	0x45450945124c8a57ULL, 0xf3f3ebf3cb18fb38ULL,
	0x3030c0309df060adULL, 0xefef9bef2b74c3c4ULL,
	0x3f3ffc3fe5c37edaULL, 0x55554955921caac7ULL,
	0xa2a2b2a2791059dbULL, 0xeaea8fea0365c9e9ULL,
	0x656589650fecca6aULL, 0xbabad2bab9686903ULL,
	0x2f2fbc2f65935e4aULL, 0xc0c027c04ee79d8eULL,
	0xdede5fdebe81a160ULL, 0x1c1c701ce06c38fcULL,
	0xfdfdd3fdbb2ee746ULL, 0x4d4d294d52649a1fULL,
	0x92927292e4e03976ULL, 0x7575c9758fbceafaULL,
	0x06061806301e0c36ULL, 0x8a8a128a249809aeULL,
	0xb2b2f2b2f940794bULL, 0xe6e6bfe66359d185ULL,
	0x0e0e380e70361c7eULL, 0x1f1f7c1ff8633ee7ULL,
	0x6262956237f7c455ULL, 0xd4d477d4eea3b53aULL,
	0xa8a89aa829324d81ULL, 0x96966296c4f43152ULL,
	0xf9f9c3f99b3aef62ULL, 0xc5c533c566f697a3ULL,
	0x2525942535b14a10ULL, 0x59597959f220b2abULL,
	0x84842a8454ae15d0ULL, 0x7272d572b7a7e4c5ULL,
	0x3939e439d5dd72ecULL, 0x4c4c2d4c5a619816ULL,
	0x5e5e655eca3bbc94ULL, 0x7878fd78e785f09fULL,
	0x3838e038ddd870e5ULL, 0x8c8c0a8c14860598ULL,
	0xd1d163d1c6b2bf17ULL, 0xa5a5aea5410b57e4ULL,
	0xe2e2afe2434dd9a1ULL, 0x616199612ff8c24eULL,
	0xb3b3f6b3f1457b42ULL, 0x2121842115a54234ULL,
	0x9c9c4a9c94d62508ULL, 0x1e1e781ef0663ceeULL,
	0x4343114322528661ULL, 0xc7c73bc776fc93b1ULL,
	0xfcfcd7fcb32be54fULL, 0x0404100420140824ULL,
	0x51515951b208a2e3ULL, 0x99995e99bcc72f25ULL,
	0x6d6da96d4fc4da22ULL, 0x0d0d340d68391a65ULL,
	0xfafacffa8335e979ULL, 0xdfdf5bdfb684a369ULL,
	0x7e7ee57ed79bfca9ULL, 0x242490243db44819ULL,
	0x3b3bec3bc5d776feULL, 0xabab96ab313d4b9aULL,
	0xcece1fce3ed181f0ULL, 0x1111441188552299ULL,
	0x8f8f068f0c890383ULL, 0x4e4e254e4a6b9c04ULL,
	0xb7b7e6b7d1517366ULL, 0xebeb8beb0b60cbe0ULL,
	0x3c3cf03cfdcc78c1ULL, 0x81813e817cbf1ffdULL,
	0x94946a94d4fe3540ULL, 0xf7f7fbf7eb0cf31cULL,
	0xb9b9deb9a1676f18ULL, 0x13134c13985f268bULL,
	0x2c2cb02c7d9c5851ULL, 0xd3d36bd3d6b8bb05ULL,
	0xe7e7bbe76b5cd38cULL, 0x6e6ea56e57cbdc39ULL,
	0xc4c437c46ef395aaULL, 0x03030c03180f061bULL,
	0x565645568a13acdcULL, 0x44440d441a49885eULL,
	0x7f7fe17fdf9efea0ULL, 0xa9a99ea921374f88ULL,
	0x2a2aa82a4d825467ULL, 0xbbbbd6bbb16d6b0aULL,
	0xc1c123c146e29f87ULL, 0x53535153a202a6f1ULL,
	0xdcdc57dcae8ba572ULL, 0x0b0b2c0b58271653ULL,
	0x9d9d4e9d9cd32701ULL, 0x6c6cad6c47c1d82bULL,
	0x3131c43195f562a4ULL, 0x7474cd7487b9e8f3ULL,
	0xf6f6fff6e309f115ULL, 0x464605460a438c4cULL,
	0xacac8aac092645a5ULL, 0x89891e893c970fb5ULL,
	0x14145014a04428b4ULL, 0xe1e1a3e15b42dfbaULL,
	0x16165816b04e2ca6ULL, 0x3a3ae83acdd274f7ULL,
	0x6969b9696fd0d206ULL, 0x09092409482d1241ULL,
	0x7070dd70a7ade0d7ULL, 0xb6b6e2b6d954716fULL,
	0xd0d067d0ceb7bd1eULL, 0xeded93ed3b7ec7d6ULL,
	0xcccc17cc2edb85e2ULL, 0x424215422a578468ULL,
	0x98985a98b4c22d2cULL, 0xa4a4aaa4490e55edULL,
	0x2828a0285d885075ULL, 0x5c5c6d5cda31b886ULL,
	0xf8f8c7f8933fed6bULL, 0x8686228644a411c2ULL,
};

static u64int cont[] = {
	0x1823c6e887b8014fULL,
	0x36a6d2f5796f9152ULL,
	0x60bc9b8ea30c7b35ULL,
	0x1de0d7c22e4bfe57ULL,
	0x157737e59ff04adaULL,
	0x58c9290ab1a06b85ULL,
	0xbd5d10f4cb3e0567ULL,
	0xe427418ba77d95d8ULL,
	0xfbee7c66dd17479eULL,
	0xca2dbf07ad5a8333ULL,
	0x6302aa71c81949d9ULL,
};

#define SB0(a) sbox[(a)]
#define SB1(a) __hsh_ror64(sbox[(a)], 8)
#define SB2(a) __hsh_ror64(sbox[(a)], 16)
#define SB3(a) __hsh_ror64(sbox[(a)], 24)
#define SB4(a) __hsh_ror64(sbox[(a)], 32)
#define SB5(a) __hsh_ror64(sbox[(a)], 40)
#define SB6(a) __hsh_ror64(sbox[(a)], 48)
#define SB7(a) __hsh_ror64(sbox[(a)], 56)

#define GB(a,i,j) ((a[(i) & 7] >> ((j) << 3)) & 255)

#define THETA_PI_GAMMA(a, i) \
(SB0(GB(a, i-0, 7)) ^        \
 SB2(GB(a, i-2, 5)) ^        \
 SB3(GB(a, i-3, 4)) ^        \
 SB1(GB(a, i-1, 6)) ^        \
 SB4(GB(a, i-4, 3)) ^        \
 SB5(GB(a, i-5, 2)) ^        \
 SB6(GB(a, i-6, 1)) ^        \
 SB7(GB(a, i-7, 0)))

static void init(ctype_hst *);
static void update(ctype_hst *, char *, usize);
static void end(ctype_hst *);
static void digest(ctype_hst *, char *);

static ctype_hmd md = {
	&init,
	&update,
	&end,
	&digest,
};

ctype_hmd *c_hsh_whirlpool = &md;

static void
init(ctype_hst *p)
{
	p->len = 0;
	c_mem_set(p->st.x64, sizeof(p->st.x64), 0);
}

static void
compress(ctype_hst *p, char *data)
{
	u64int k[2][8], t[3][8];
	int i, j;

	k[0][0] = p->st.x64[0];
	k[0][1] = p->st.x64[1];
	k[0][2] = p->st.x64[2];
	k[0][3] = p->st.x64[3];
	k[0][4] = p->st.x64[4];
	k[0][5] = p->st.x64[5];
	k[0][6] = p->st.x64[6];
	k[0][7] = p->st.x64[7];
	for (i = 0; i < 8; ++i) {
		t[0][i] = c_uint_64bigunpack(data + (i << 3));
		t[2][i] = t[0][i];
		t[0][i] ^= k[0][i];
	}
	for (i = 0; i < 10; i += 2) {
		/* odd round */
		for (j = 0; j < 8; ++j)
			k[1][j] = THETA_PI_GAMMA(k[0], j);

		k[1][0] ^= cont[i];

		for (j = 0; j < 8; ++j)
			t[1][j] = THETA_PI_GAMMA(t[0], j) ^ k[1][j];

		/* even round */
		for (j = 0; j < 8; ++j)
			k[0][j] = THETA_PI_GAMMA(k[1], j);

		k[0][0] ^= cont[i + 1];

		for (j = 0; j < 8; ++j)
			t[0][j] = THETA_PI_GAMMA(t[1], j) ^ k[0][j];
	}
	p->st.x64[0] ^= t[0][0] ^ t[2][0];
	p->st.x64[1] ^= t[0][1] ^ t[2][1];
	p->st.x64[2] ^= t[0][2] ^ t[2][2];
	p->st.x64[3] ^= t[0][3] ^ t[2][3];
	p->st.x64[4] ^= t[0][4] ^ t[2][4];
	p->st.x64[5] ^= t[0][5] ^ t[2][5];
	p->st.x64[6] ^= t[0][6] ^ t[2][6];
	p->st.x64[7] ^= t[0][7] ^ t[2][7];
}

static void
update(ctype_hst *p, char *data, usize n)
{
	__hsh_update(compress, 64, p, data, n);
}

static void
end(ctype_hst *p)
{
	uint r;

	r = p->len % 64;
	p->buf[r++] = 0x80;
	if (r > 32) {
		c_mem_set(p->buf + r, 64 - r, 0);
		compress(p, (char *)p->buf);
		r = 0;
	}
	c_mem_set(p->buf + r, 56 - r, 0);
	c_uint_64bigpack((char *)p->buf + 56, p->len << 3);
	compress(p, (char *)p->buf);
}

static void
digest(ctype_hst *p, char *s)
{
	int i;

	for (i = 0; i < 8; ++i)
		c_uint_64bigpack(s + (i << 3), p->st.x64[i]);
}
