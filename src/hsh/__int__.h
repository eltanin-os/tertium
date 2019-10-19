void __hsh_update(void (*)(ctype_hst *, char *), int,
    ctype_hst *, char *, usize);

static inline u32int
__hsh_rol32(u32int n, int k)
{
	return ((n << k) | (n >> (32 - k)));
}

static inline u32int
__hsh_ror32(u32int n, int k)
{
	return ((n >> k) | (n << (32 - k)));
}

static inline u64int
__hsh_ror64(u64int n, int k)
{
	return ((n >> k) | (n << (64 - k)));
}
