#define UTF8_RANGESEARCH(a, b) \
c_std_bsearch((a), (b), (C_STD_NELEM((b))>>1), \
    (sizeof(*(b))<<1), &_tertium_utf8_rangecmp)

#define UTF8_SEARCH(a, b) \
c_std_bsearch((a), (b), C_STD_NELEM((b)), sizeof(*(b)), _tertium_utf8_cmp)

int _tertium_utf8_rangecmp(void *, void *);
int _tertium_utf8_cmp(void *, void *);

extern uchar *_tertium_utf8_mtab;
