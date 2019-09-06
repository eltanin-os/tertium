u32int __hsh_rol32(u32int, int);
u32int __hsh_ror32(u32int, int);
u64int __hsh_ror64(u64int, int);

void __hsh_update(void (*)(ctype_hst *, char *), int,
    ctype_hst *, char *, usize);
