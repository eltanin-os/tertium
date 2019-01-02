struct fmtverb {
	int c;
	int (*f)(Fmt *);
};

extern Membuf Fmts;
extern struct fmtverb VFmts[];
