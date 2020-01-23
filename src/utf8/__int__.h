#define __UTF8_RANGESEARCH(a, b) \
c_std_bsearch((a), (b), (C_NELEM((b))>>1), (sizeof(*(b))<<1), &__utf8_rangecmp)
#define __UTF8_SEARCH(a, b) \
c_std_bsearch((a), (b), C_NELEM((b)), sizeof(*(b)), __utf8_cmp)

int __utf8_rangecmp(void *, void *);
int __utf8_cmp(void *, void *);
