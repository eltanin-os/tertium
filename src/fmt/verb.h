struct fmtverb {
	int c;
	int (*f)(CFmt *);
};

extern CArr Fmts;
extern struct fmtverb VFmts[];
extern int trycat(CFmt *, char *, usize, usize);
