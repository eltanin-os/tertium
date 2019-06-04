struct fmtverb {
	int c;
	int (*f)(CFmt *);
};

extern CArr __fmt_Fmts;
extern struct fmtverb __fmt_VFmts[];
extern int __fmt_trycat(CFmt *, char *, usize, usize);
