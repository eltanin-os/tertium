#define ARGBEGIN \
for (argc--, argv++;\
     *argv && (*argv)[0] == '-' && (*argv)[1]; argc--, argv++) {\
	char _argc, _brk;\
	if ((*argv)[1] == '-' && (*argv)[2] == '\0') {\
		argc -= 1, argv += 1;\
		break;\
	}\
	for (_brk = 0, argv[0]++; (*argv)[0] && !_brk; argv[0]++) {\
		_argc = (*argv)[0];\
		switch (_argc)
#define ARGF() \
(((*argv)[1] == '\0' && !argv[1]) ? (char *)0 :\
(_brk = 1, ((*argv)[1] != '\0') ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define EARGF(x) \
(((*argv)[1] == '\0' && !argv[1]) ? ((x), abort(), (char *)0) :\
(_brk = 1, ((*argv)[1] != '\0') ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define ARGC() _argc
#define ARGEND } }

#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define NELEM(a)  (sizeof((a))/sizeof((a)[0]))

#define getprogname( ) argv0
#define setprogname(x) argv0 = (x)

#define offsetof(a, b) (ulong)(&(((a *)0)->b))

/* arr macros */
#define c_arr_INIT(a) { sizeof((a)), 0, (a) }

/* chr macros */
#define c_chr_isspace(a) ((a) == ' ' || (uint)(a) - '\t' < 5)

/* fmt macros */
enum {
	FmtWidth    = 1 << 0,
	FmtLeft     = 1 << 1,
	FmtPrec     = 1 << 2,
	FmtSharp    = 1 << 3,
	FmtSpace    = 1 << 4,
	FmtSign     = 1 << 5,
	FmtZero     = 1 << 6,
	FmtUnsigned = 1 << 7,
	FmtShort    = 1 << 8,
	FmtLong     = 1 << 9,
	FmtVLong    = 1 << 10,
	FmtComma    = 1 << 11,
	FmtByte     = 1 << 12,
	FmtFlag     = 1 << 13,
};

/* ioq macros */
#define FD0 0
#define FD1 1
#define FD2 2
#define IOQBUFSIZ 8192
#define ERRBUFSIZ 512
#define c_ioq_INIT(a, b, c) {(b), (c), (a) }

typedef struct Membuf Membuf;

struct Membuf {
	usize  a;
	usize  n;
	uchar *p;
};

typedef struct Fmt Fmt;

struct Fmt {
	Membuf  *mb;
	va_list  args;
	size   (*op)(int, void *, usize);
	int    (*fn)(Fmt *);
	int      nfmt;
	int      prec;
	int      r;
	int      width;
	ushort   flags;
	void    *farg;
};

typedef struct Stat Stat;

struct Stat {
	vlong  st_size;
	ulong  st_blksize;
	ulong  st_blocks;
	long   st_atime;
	long   st_ctime;
	long   st_mtime;
	short  st_gid;
	short  st_nlink;
	short  st_uid;
	ushort st_dev;
	ushort st_ino;
	ushort st_mode;
	ushort st_rdev;
};

typedef struct Ioq Ioq;

struct Ioq {
	Membuf *mb;
	size  (*op)(int, void *, usize);
	int     fd;
};

/* arr routines */
usize  c_arr_avail(Membuf *);
int    c_arr_cat(Membuf *, void *, usize, usize);
size   c_arr_fmt(Membuf *, char *, ...);
void * c_arr_get(Membuf *, usize, usize);
void   c_arr_init(Membuf *, char *, usize);
usize  c_arr_len(Membuf *, usize);
int    c_arr_trunc(Membuf *, usize, usize);
size   c_arr_vfmt(Membuf *, char *, va_list);

/* dir routines */
int c_dir_open(Dir *, char *, int);
int c_dir_read(Dir *, Dirent *);
int c_dir_close(Dir *);

/* dyn routines */
void * c_dyn_alloc(Membuf *, usize, usize);
int    c_dyn_cat(Membuf *, void *, usize, usize);
size   c_dyn_fmt(Membuf *, char *, ...);
size   c_dyn_vfmt(Membuf *, char *, va_list);

/* fmt routines */
int  c_fmt_fdflush(Fmt *);
void c_fmt_fdinit(Fmt *, int, Membuf *, size (*)(int, void *, usize));
size c_fmt_fmt(Fmt *, char *);
int  c_fmt_install(int, int (*)(Fmt *));

/* ioq routines */
size   c_ioq_feed(Ioq *);
int    c_ioq_flush(Ioq *);
size   c_ioq_fmt(Ioq *, char *, ...);
size   c_ioq_get(Ioq *, char *, usize);
int    c_ioq_getln(Ioq *, Membuf *);
void   c_ioq_init(Ioq *, int, Membuf *, size (*)(int, void *, usize));
int    c_ioq_nput(Ioq *, char *, usize);
void * c_ioq_peek(Ioq *);
int    c_ioq_put(Ioq *, char *);
int    c_ioq_putfd(Ioq *, int, usize);
int    c_ioq_putfile(Ioq *, char *);
void   c_ioq_seek(Ioq *, usize);
size   c_ioq_vfmt(Ioq *, char *, va_list);

/* mem routines */
void * c_mem_ccpy(void *, void *, usize, int);
void * c_mem_chr(void *, usize, int);
int    c_mem_cmp(void *, void *, usize);
void * c_mem_cpy(void *, void *, usize);
int    c_mem_equal(void *, void *, usize);
void * c_mem_mem(void *, usize, void *, usize);
void * c_mem_rchr(void *, usize, int);
void * c_mem_set(void *, usize, int);

/* std routines */
void * c_std_alloc(usize, usize);
void * c_std_calloc(usize, usize);
void   c_std_exit(int);
void   c_std_free(void *);
void * c_std_realloc(void *, usize, usize);
void   c_std_sort(void *, usize, usize, int (*)(void *, void *));
vlong  c_std_strtovl(char *, int, vlong, vlong, char **, int *);

/* sys routines */
void   c_sys_abort(void);
int    c_sys_chdir(char *);
int    c_sys_close(int);
long   c_sys_conf(int);
int    c_sys_dup(int);
int    c_sys_errstr(char *, usize);
void   c_sys_exit(int);
int    c_sys_fchdir(int);
int    c_sys_fstat(Stat *, int);
char * c_sys_getenv(char *);
short  c_sys_getgid(void);
short  c_sys_getuid(void);
int    c_sys_lstat(Stat *, char *);
void * c_sys_mmap(void *, usize, int, int, int, int);
int    c_sys_munmap(void *, usize);
int    c_sys_open(char *, int, int);
size   c_sys_read(int, void *, usize);
vlong  c_sys_seek(int, vlong, int);
int    c_sys_stat(Stat *, char *);
int    c_sys_unlink(char *);
size   c_sys_write(int, void *, usize);

extern Ioq *ioq0;
extern Ioq *ioq1;
extern Ioq *ioq2;
extern char *argv0;
extern char **environ;
