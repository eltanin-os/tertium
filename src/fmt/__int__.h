struct fmtverb {
	int c;
	ctype_status (*f)(ctype_fmt *);
};

extern ctype_arr __fmt_Fmts;
extern struct fmtverb __fmt_VFmts[];
extern ctype_status __fmt_trycat(ctype_fmt *, char *, usize);
