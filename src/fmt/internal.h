#define VFMTLEN 20

struct fmtverb {
	ctype_rune c;
	ctype_status (*f)(ctype_fmt *);
};

extern ctype_arr _tertium_fmt_fmts;
extern struct fmtverb _tertium_fmt_vfmts[];
extern ctype_status _tertium_fmt_trycat(ctype_fmt *, char *, usize);
