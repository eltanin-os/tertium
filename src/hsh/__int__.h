#define ROL(a, b) \
((((u32int)(a)<<(u32int)((b)&31)) | \
 (((u32int)(a)&0xFFFFFFFFUL)>>(u32int)((32-((b)&31))&31))) & 0xFFFFFFFFUL)

#define ROR(a, b) \
(((((u32int)(a)&0xFFFFFFFFUL)>>(u32int)((b)&31)) | \
  ((u32int)(a)<<(u32int)((32-((b)&31))&31))) & 0xFFFFFFFFUL)

void __hsh_update(void (*)(CHst *, char *), int, CHst *, char *, usize);
