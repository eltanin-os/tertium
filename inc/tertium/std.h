#include <tertium/os.h>

/* arg macros */
#define C_ARGBEGIN \
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
#define C_ARGF() \
(((*argv)[1] == '\0' && !argv[1]) ? (char *)0 :\
(_brk = 1, ((*argv)[1] != '\0') ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define C_EARGF(x) \
(((*argv)[1] == '\0' && !argv[1]) ? ((x), c_sys_abort(), (char *)0) :\
(_brk = 1, ((*argv)[1] != '\0') ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define C_ARGC() _argc
#define C_ARGEND } }

/* arr macros */
#define c_arr_INIT(a) { sizeof((a)), 0, (a) }

/* chr macros */
#define c_chr_isspace(a) ((a) == ' ' || (uint)(a) - '\t' < 5)

/* dir macros */
enum {
	C_FSLOG = 1 << 0,
	C_FSPHY = 1 << 1,
	C_FSCOM = 1 << 2,
	C_FSNOI = 1 << 3,
	C_FSDOT = 1 << 4,
	C_FSXDV = 1 << 5,
};

#define C_FSFLW(a, b) (((a) & C_FSLOG) || (((a) & C_FSCOM) && !(b)))

/* fmt macros */
enum {
	C_FMTWIDTH    = 1 << 0,
	C_FMTLEFT     = 1 << 1,
	C_FMTPREC     = 1 << 2,
	C_FMTSHARP    = 1 << 3,
	C_FMTSPACE    = 1 << 4,
	C_FMTSIGN     = 1 << 5,
	C_FMTZERO     = 1 << 6,
	C_FMTUNSIGNED = 1 << 7,
	C_FMTSHORT    = 1 << 8,
	C_FMTLONG     = 1 << 9,
	C_FMTVLONG    = 1 << 10,
	C_FMTCOMMA    = 1 << 11,
	C_FMTBYTE     = 1 << 12,
	C_FMTFLAG     = 1 << 13,
};

/* general macros */
#define C_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define C_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define C_NELEM(a)  (sizeof((a))/sizeof((a)[0]))

#define C_ISDOT(a)  ((a)[0]=='.' && ((a)[1]==0 || ((a)[1]=='.' && (a)[2]==0)))
#define C_ISDASH(a) ((a)[0]=='-' && (a)[1]=='\0')

#define C_OFLW_UM(a, b, c) ((b) && (c) > (a)-1/(b))
#define C_OFLW_UA(a, b)    ((b) > (a)-1)

#define C_HOWMANY(a, b) (((a)+((b)-1))/(b))

/* ioq macros */
#define C_FD0 0
#define C_FD1 1
#define C_FD2 2
#define C_BIOSIZ 8192
#define C_ERRSIZ 512
#define c_ioq_INIT(a, b, c) { (b), (c), (a) }

/* std macros */
#define c_std_free(a) a = c_std_free_((a))
#define c_std_getprogname( ) argv0
#define c_std_offsetof(a, b) (ulong)(&(((a *)0)->b))
#define c_std_setprogname(a) argv0 = (a)

/* tai macros */
#define C_TAI_PACK 8

/* tna macros */
#define C_TAIA_PACK 16

/* sys macros */
#define c_sys_call(...) c_sys_call_(__VA_ARGS__, nil)

/* arr types */
typedef struct CArr CArr;

struct CArr {
	usize  a;
	usize  n;
	uchar *p;
};


/* dst types */
typedef struct CNode  CNode;
typedef struct CQueue CQueue;

struct CNode {
	CNode *next;
	CNode *prev;
	void  *p;
};

struct CQueue {
	CArr  mb;
	usize h;
};

/* fmt types */
typedef struct CFmt CFmt;

struct CFmt {
	CArr    *mb;
	va_list  args;
	size   (*op)(int, void *, usize);
	int    (*fn)(CFmt *);
	usize    nfmt;
	int      prec;
	int      r;
	int      width;
	ulong    flags;
	void    *farg;
};

/* hsh types */
typedef struct CH32md CH32md;
typedef struct CH32st CH32st;

struct CH32md {
	int (*init)(CH32st *);
	int (*update)(CH32st *, char *, usize);
	int (*end)(CH32st *);
};

struct CH32st {
	u32int a;
	u32int b;
};

/* ioq types */
typedef struct CIoq CIoq;

struct CIoq {
	CArr  *mb;
	size (*op)(int, void *, usize);
	int    fd;
};

/* sys types */
typedef struct CTime CTime;
typedef struct CStat CStat;

struct CTime {
	long tv_sec;
	long tv_nsec;
};

struct CStat {
	CTime  st_atim;
	CTime  st_ctim;
	CTime  st_mtim;
	ulong  st_blksize;
	ulong  st_blocks;
	ulong  st_dev;
	ulong  st_ino;
	ulong  st_rdev;
	vlong  st_size;
	int    st_gid;
	int    st_nlink;
	int    st_uid;
	ushort st_mode;
};

/* dir types */
typedef struct CDent CDent;
typedef struct CDir  CDir;

struct CDent {
	CStat  info;
	ushort nlen;
	ushort plen;
	char  *name;
	char   path[C_PATHMAX];
};

struct CDir {
	ulong  dev;
	int    fd;
	uint   opts;
	short  a;
	short  n;
	ushort len;
	char   buf[2048];
	char   path[C_PATHMAX];
};

/* tai types */
typedef struct CTai CTai;

struct CTai {
	u64int x;
};

/* tna types */
typedef struct CTaia CTaia;

struct CTaia {
	CTai  sec;
	ulong atto;
	ulong nano;
};

/* arr routines */
usize  c_arr_avail(CArr *);
usize  c_arr_bytes(CArr *);
size   c_arr_cat(CArr *, void *, usize, usize);
size   c_arr_cats(CArr *, char *);
size   c_arr_fmt(CArr *, char *, ...);
void * c_arr_bget(CArr *, usize);
void * c_arr_get(CArr *, usize, usize);
void   c_arr_init(CArr *, char *, usize);
usize  c_arr_len(CArr *, usize);
int    c_arr_trunc(CArr *, usize, usize);
size   c_arr_vfmt(CArr *, char *, va_list);

/* dir routines */
int c_dir_close(CDir *);
int c_dir_hist(CNode **, CStat *);
int c_dir_open(CDir *, char *, uint);
int c_dir_read(CDent *, CDir *);

/* dst routines */
void    c_dst_lfree(CNode *);
CNode * c_dst_lnew(void *, usize, usize);
CNode * c_dst_lpop(CNode **);
int     c_dst_lpush(CNode **, CNode *);
void    c_dst_lsort(CNode **, int (*)(void *, void *));
void    c_dst_qinit(CQueue *, char *, usize);
int     c_dst_qpop(CQueue *, CArr *, usize, usize);
int     c_dst_qpops(CQueue *, CArr *);
int     c_dst_qpush(CQueue *, void *, usize, usize);

/* dyn routines */
void * c_dyn_alloc(CArr *, usize, usize);
size   c_dyn_cat(CArr *, void *, usize, usize);
size   c_dyn_cats(CArr *, char *);
size   c_dyn_fmt(CArr *, char *, ...);
void   c_dyn_free(CArr *);
size   c_dyn_vfmt(CArr *, char *, va_list);

/* err routines */
void c_err_die(int, char *, ...);
void c_err_diex(int, char *, ...);
void c_err_vdie(int, char *, va_list);
void c_err_vdiex(int, char *, va_list);
int  c_err_vwarn(char *, va_list);
int  c_err_vwarnx(char *, va_list);
int  c_err_warn(char *, ...);
int  c_err_warnx(char *, ...);

/* exc routines */
int c_exc_run(char *, char **);
int c_exc_runenv(char *, char **, char **);
int c_exc_setenv(char *, char *);

/* fmt routines */
int  c_fmt_fdflush(CFmt *);
void c_fmt_fdinit(CFmt *, int, CArr *, size (*)(int, void *, usize));
size c_fmt_fmt(CFmt *, char *);
int  c_fmt_install(int, int (*)(CFmt *));

/* gen routines */
char * c_gen_basename(char *);
char * c_gen_dirname(char *);

/* hsh routines */
u32int c_hsh_all(CH32md *, char *, usize);
u32int c_hsh_putfile(CH32md *, char *);
u32int c_hsh_putfd(CH32md *, int, usize);

/* ioq routines */
size   c_ioq_feed(CIoq *);
int    c_ioq_flush(CIoq *);
size   c_ioq_fmt(CIoq *, char *, ...);
size   c_ioq_get(CIoq *, char *, usize);
int    c_ioq_getln(CIoq *, CArr *);
void   c_ioq_init(CIoq *, int, CArr *, size (*)(int, void *, usize));
size   c_ioq_nput(CIoq *, char *, usize);
void * c_ioq_peek(CIoq *);
size   c_ioq_put(CIoq *, char *);
int    c_ioq_putfd(CIoq *, int, usize);
int    c_ioq_putfile(CIoq *, char *);
void   c_ioq_seek(CIoq *, usize);
size   c_ioq_vfmt(CIoq *, char *, va_list);

/* mem routines */
void * c_mem_ccpy(void *, usize, void *, int);
void * c_mem_chr(void *, usize, int);
int    c_mem_cmp(void *, usize, void *);
void * c_mem_cpy(void *, usize, void *);
int    c_mem_equal(void *, usize, void *);
void * c_mem_mem(void *, usize, void *, usize);
void * c_mem_rchr(void *, usize, int);
void * c_mem_set(void *, usize, int);

/* std routines */
void * c_std_alloc(usize, usize);
void * c_std_bsearch(void *, void *, usize, usize, int (*)(void *, void *));
void * c_std_calloc(usize, usize);
void   c_std_exit(int);
void * c_std_free_(void *);
void * c_std_realloc(void *, usize, usize);
void   c_std_sort(void *, usize, usize, int (*)(void *, void *));
vlong  c_std_strtovl(char *, int, vlong, vlong, char **, int *);

/* str routines */
char * c_str_chr(char *, usize, int);
int    c_str_cmp(char *, usize, char *);
usize  c_str_len(char *, usize);
char * c_str_str(char *, usize, char *);

/* sys routines */
void   c_sys_abort(void);
size   c_sys_allrw(size (*)(int, void *, usize), int, void *, usize);
vlong  c_sys_call_(vlong, ...);
int    c_sys_chdir(char *);
int    c_sys_close(int);
long   c_sys_conf(int);
int    c_sys_dup(int, int);
int    c_sys_errstr(char *, usize);
int    c_sys_exec(char *, char **, char **);
void   c_sys_exit(int);
int    c_sys_fchdir(int);
int    c_sys_fstat(CStat *, int);
char * c_sys_getcwd(char *, usize);
char * c_sys_getenv(char *);
short  c_sys_getgid(void);
char * c_sys_getsyserr(void);
int    c_sys_gettime(int, CTime *);
short  c_sys_getuid(void);
int    c_sys_link(char *, char *);
int    c_sys_lstat(CStat *, char *);
void * c_sys_mmap(void *, usize, int, int, int, int);
int    c_sys_munmap(void *, usize);
int    c_sys_open(char *, int, int);
size   c_sys_read(int, void *, usize);
int    c_sys_rmdir(char *);
vlong  c_sys_seek(int, vlong, int);
int    c_sys_stat(CStat *, char *);
char * c_sys_strerror(int, char *, usize);
int    c_sys_unlink(char *);
void   c_sys_werrstr(char *, ...);
size   c_sys_write(int, void *, usize);

/* tai routines */
void   c_tai_add(CTai *, CTai *, CTai *);
double c_tai_approx(CTai *);
int    c_tai_less(CTai *, CTai *);
void   c_tai_pack(char *, CTai *);
void   c_tai_now(CTai *);
void   c_tai_sub(CTai *, CTai *, CTai *);
void   c_tai_unpack(char *, CTai *);

/* tna routines */
void   c_tna_add(CTaia *, CTaia *, CTaia *);
double c_tna_approx(CTaia *);
double c_tna_frac(CTaia *);
void   c_tna_half(CTaia *, CTaia *);
int    c_tna_less(CTaia *, CTaia *);
void   c_tna_now(CTaia *);
void   c_tna_pack(char *, CTaia *);
void   c_tna_sub(CTaia *, CTaia *, CTaia *);
void   c_tna_tai(CTaia *, CTai *);
void   c_tna_unpack(char *, CTaia *);

/* hsh variables */
extern CH32md *c_hsh_crc32b;
extern CH32md *c_hsh_crc32p;
extern CH32md *c_hsh_edf;
extern CH32md *c_hsh_fletcher16;

/* ioq variables */
extern CIoq *ioq0;
extern CIoq *ioq1;
extern CIoq *ioq2;

/* std variables */
extern char *argv0;
extern char **environ;
