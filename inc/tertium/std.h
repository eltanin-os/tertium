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
((!((*argv)[1]) && !(argv[1])) ? nil :\
(_brk = 1, ((*argv)[1]) ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define C_EARGF(x) \
((!((*argv)[1]) && !(argv[1])) ? ((x), c_std_abort(), nil) :\
(_brk = 1, ((*argv)[1]) ? (&(*argv)[1]) : (argc--, argv++, *argv)))
#define C_ARGC() _argc
#define C_ARGEND } }

/* arr macros */
#define c_arr_INIT(a) { sizeof((a)), 0, (a) }

/* chr macros */
#define c_chr_isspace(a) ((a) == ' ' || (uint)(a) - '\t' < 5)

/* dir macros */
enum {
	/* instr */
	C_FSAGN = 1,
	C_FSFLW = 2,
	C_FSSKP = 3,

	/* opts */
	C_FSLOG = 1 << 0,
	C_FSPHY = 1 << 1,
	C_FSCOM = 1 << 2,
	C_FSNOI = 1 << 3,
	C_FSVDT = 1 << 4,
	C_FSXDV = 1 << 5,
	C_FSDRL = 1 << 6,
	C_FSFHT = 1 << 7,
	C_FSSTP = 1 << 8,

	/* types */
	C_FSD = 1,
	C_FSDC = 2,
	C_FSDEF = 3,
	C_FSDNR = 4,
	C_FSDOT = 5,
	C_FSDP = 6,
	C_FSERR = 7,
	C_FSF = 8,
	C_FSFC = 9,
	C_FSNS = 10,
	C_FSSL = 11,
	C_FSSLN = 12,
	C_FSINT = 13,
};

/* dyn macros */
#define C_DYNMINALLOC 64

/* fmt macros */
enum {
	C_FMTWIDTH = 1 << 0,
	C_FMTLEFT = 1 << 1,
	C_FMTPREC = 1 << 2,
	C_FMTSHARP = 1 << 3,
	C_FMTSPACE = 1 << 4,
	C_FMTSIGN = 1 << 5,
	C_FMTZERO = 1 << 6,
	C_FMTUNSIGNED = 1 << 7,
	C_FMTSHORT = 1 << 8,
	C_FMTLONG = 1 << 9,
	C_FMTVLONG = 1 << 10,
	C_FMTCOMMA = 1 << 11,
	C_FMTBYTE = 1 << 12,
	C_FMTFLAG = 1 << 13,
};

/* general macros */
#define C_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define C_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define C_NELEM(a)  (sizeof((a))/sizeof((a)[0]))

#define C_ISDOT(a)  ((a)[0]=='.' && ((a)[1]==0 || ((a)[1]=='.' && (a)[2]==0)))
#define C_ISDASH(a) ((a)[0]=='-' && (a)[1]=='\0')

#define C_OFLW_UM(a, b, c) ((b) && (c) > (((a)-1)/(b)))
#define C_OFLW_UA(a, b, c) ((c) > (((a)-1)-(b)))

#define C_HOWMANY(a, b) (((a)+((b)-1))/(b))

/* hsh macros */
enum {
	C_H32GEN_DIGEST = 32,
	C_HMD5_DIGEST = 16,
	C_HSHA1_DIGEST = 20,
	C_HSHA256_DIGEST = 32,
	C_HSHA512_DIGEST = 64,
	C_HWHIRLPOOL_DIGEST = 64,
};

/* ioq macros */
enum {
	/* default file descriptors */
	C_FD0 = 0,
	C_FD1 = 1,
	C_FD2 = 2,

	/* sizes */
	C_BIOSIZ = 8192,
	C_ERRSIZ = 512,

	/* flags */
	C_IOQ_ONOFLUSH = 1 << 0,
	__IOQ_OALL = 1 << 0,
};

#define c_ioq_INIT(a, b, c) { { sizeof((b)), 0, (b) }, (c), (a), 0 }

/* std macros */
#define c_std_free(a) a = c_std_free_((a))
#define c_std_getprogname( ) argv0
#define c_std_offsetof(a, b) (ulong)(&(((a *)0)->b))
#define c_std_setprogname(a) argv0 = (a)
#define c_std_syscall(...) c_std_syscall_(__VA_ARGS__, nil)

/* tai macros */
#define C_TAI_PACK 8

/* taia macros */
#define C_TAIA_PACK 16

/* utf8 macros */
#define C_RUNEERROR 0xFFFD
#define C_RUNEMAX 0x10FFFF
#define C_UTFMAX 6

/* arr types */
typedef struct ctype_arr ctype_arr;

struct ctype_arr {
	usize a;
	usize n;
	uchar *p;
};

/* cal types */
typedef struct ctype_caldate ctype_caldate;
typedef struct ctype_caltime ctype_caltime;

struct ctype_caldate {
	long year;
	int day;
	int month;
};

struct ctype_caltime {
	ctype_caldate date;
	long offset;
	int hour;
	int minute;
	int second;
};

/* adt types */
typedef struct ctype_node ctype_node;

struct ctype_node {
	ctype_node *next;
	ctype_node *prev;
	void *p;
};

/* dir types */
typedef struct ctype_dent ctype_dent;
typedef struct ctype_dir ctype_dir;

struct ctype_dent {
	ctype_dent *parent;
	ctype_stat *stp;
	vlong num;
	ctype_fsid dev;
	usize len;
	usize nlen;
	ushort instr;
	ushort info;
	int err;
	int depth;
	char *path;
	char *name;
	void *ptr;
	void *__p;		/* (private) */
};

struct ctype_dir {
	ctype_node *cur;
	ctype_node *ccur;
	ctype_node *child;
	ctype_arr hist;
	ctype_fsid dev;
	ctype_cmpfn f;
	uint opts;
};

/* fmt types */
typedef struct ctype_fmt ctype_fmt;
typedef ctype_status (*ctype_fmtopfn)(ctype_fmt *, char *, usize);
typedef ctype_status (*ctype_fmtfn)(ctype_fmt *);

struct ctype_fmt {
	ctype_arr *mb;
	va_list args;
	ctype_fmtopfn func;
	usize nfmt;
	int prec;
	int r;
	int width;
	ulong flags;
	void *farg;
};

/* hsh types */
typedef struct ctype_hmd ctype_hmd;
typedef struct ctype_hst ctype_hst;

struct ctype_hmd {
	void (*init)(ctype_hst *);
	void (*update)(ctype_hst *, char *, usize);
	void (*end)(ctype_hst *);
	void (*digest)(ctype_hst *, char *);
};

struct ctype_hst {
	union {
		u32int x32[16];
		u64int x64[8];
	} st;
	uchar buf[128];
	usize len;
};

/* ioq types */
typedef struct ctype_ioq ctype_ioq;

struct ctype_ioq {
	ctype_arr arr;
	ctype_iofn op;
	ctype_fd fd;
	uchar opts;
};

/* cdb types */
typedef struct ctype_cdb ctype_cdb;
typedef struct ctype_cdbmk ctype_cdbmk;

struct ctype_cdb {
	u32int dpos;
	u32int dlen;
	u32int hpos;
	u32int hslots;
	u32int khash;
	u32int kpos;
	u32int loop;
	u32int size;
	ctype_fd fd;
	uchar *map;
};

struct ctype_cdbmk {
	ctype_arr hplist;
	ctype_ioq ioq;
	u32int off;
	ctype_fd fd;
	char buf[C_BIOSIZ];
};

/* tai types */
typedef struct ctype_tai ctype_tai;

struct ctype_tai {
	u64int x;
};

/* taia types */
typedef struct ctype_taia ctype_taia;

struct ctype_taia {
	ctype_tai sec;
	ulong atto;
	ulong nano;
};

/* adt routines */
void c_adt_lfree(ctype_node *);
ctype_node *c_adt_lnew(void *, usize);
ctype_node *c_adt_lpop(ctype_node **);
ctype_status c_adt_lpush(ctype_node **, ctype_node *);
void c_adt_lsort(ctype_node **, ctype_cmpfn);
ctype_status c_adt_ltpush(ctype_node **, ctype_node *);
ctype_node *c_adt_ltpop(ctype_node **);

/* arr routines */
usize c_arr_avail(ctype_arr *);
usize c_arr_bytes(ctype_arr *);
ctype_status c_arr_cat(ctype_arr *, void *, usize, usize);
void *c_arr_data(ctype_arr *);
size c_arr_fmt(ctype_arr *, char *, ...);
void *c_arr_get(ctype_arr *, usize, usize);
void c_arr_init(ctype_arr *, char *, usize);
usize c_arr_len(ctype_arr *, usize);
usize c_arr_total(ctype_arr *);
ctype_status c_arr_trunc(ctype_arr *, usize, usize);
size c_arr_vfmt(ctype_arr *, char *, va_list);

/* cal routines */
void c_cal_datefrommjd(ctype_caldate *, long);
long c_cal_datemjd(ctype_caldate *);
void c_cal_datenorm(ctype_caldate *);
void c_cal_timetai(ctype_tai *, ctype_caltime *);
void c_cal_timeutc(ctype_caltime *, ctype_tai *);

/* cdb routines */
u32int c_cdb_datalen(ctype_cdb *);
u32int c_cdb_datapos(ctype_cdb *);
ctype_status c_cdb_find(ctype_cdb *, char *, usize);
ctype_status c_cdb_findnext(ctype_cdb *, char *, usize);
void c_cdb_findstart(ctype_cdb *);
void c_cdb_free(ctype_cdb *);
u32int c_cdb_hash(char *, usize);
u32int c_cdb_hashadd(u32int, uchar);
ctype_status c_cdb_init(ctype_cdb *, ctype_fd);
ctype_status c_cdb_mkadd(ctype_cdbmk *, char *, usize, char *, usize);
ctype_status c_cdb_mkaddbegin(ctype_cdbmk *, usize, usize);
ctype_status c_cdb_mkaddend(ctype_cdbmk *, usize, usize, u32int);
ctype_status c_cdb_mkfinish(ctype_cdbmk *);
ctype_status c_cdb_mkstart(ctype_cdbmk *, ctype_fd);
ctype_status c_cdb_read(ctype_cdb *, char *, usize, u32int);

/* dir routines */
ctype_dent *c_dir_children(ctype_dir *);
ctype_status c_dir_close(ctype_dir *);
ctype_dent *c_dir_list(ctype_dir *);
ctype_status c_dir_open(ctype_dir *, char **, uint, ctype_cmpfn);
ctype_dent *c_dir_read(ctype_dir *);
ctype_status c_dir_set(ctype_dir *, ctype_dent *, int);

/* dyn routines */
void *c_dyn_alloc(ctype_arr *, usize, usize);
ctype_status c_dyn_cat(ctype_arr *, void *, usize, usize);
size c_dyn_fmt(ctype_arr *, char *, ...);
void c_dyn_free(ctype_arr *);
ctype_status c_dyn_ready(ctype_arr *, usize, usize);
void c_dyn_shrink(ctype_arr *);
size c_dyn_vfmt(ctype_arr *, char *, va_list);

/* err routines */
void c_err_die(int, char *, ...);
void c_err_diex(int, char *, ...);
void c_err_vdie(int, char *, va_list);
void c_err_vdiex(int, char *, va_list);
int c_err_vwarn(char *, va_list);
int c_err_vwarnx(char *, va_list);
int c_err_warn(char *, ...);
int c_err_warnx(char *, ...);

/* exc routines */
ctype_status c_exc_run(char *, char **);
ctype_status c_exc_runenv(char *, char **, char **);
ctype_status c_exc_setenv(char *, char *);

/* fmt routines */
void c_fmt_init(ctype_fmt *, void *, ctype_arr *, ctype_fmtopfn);
size c_fmt_fmt(ctype_fmt *, char *);
ctype_status c_fmt_install(int, ctype_fmtfn);

/* gen routines */
char *c_gen_basename(char *);
char *c_gen_dirname(char *);

/* hsh routines */
void c_hsh_all(ctype_hst *, ctype_hmd *, char *, usize);
void c_hsh_digest(ctype_hst *, ctype_hmd *, char *);
usize c_hsh_len(ctype_hst *);
ctype_status c_hsh_putfd(ctype_hst *, ctype_hmd *, ctype_fd, usize);
ctype_status c_hsh_putfile(ctype_hst *, ctype_hmd *, char *);

/* ioq routines */
ctype_ioq *c_ioq_alloc(ctype_fd, usize, ctype_iofn);
size c_ioq_feed(ctype_ioq *);
ctype_fd c_ioq_fileno(ctype_ioq *);
ctype_status c_ioq_flush(ctype_ioq *);
size c_ioq_fmt(ctype_ioq *, char *, ...);
void c_ioq_free(ctype_ioq *);
size c_ioq_get(ctype_ioq *, char *, usize);
size c_ioq_getall(ctype_ioq *, char *, usize);
ctype_status c_ioq_getdelim(ctype_ioq *, ctype_arr *, int);
ctype_status c_ioq_getln(ctype_ioq *, ctype_arr *);
void c_ioq_init(ctype_ioq *, ctype_fd, char *, usize, ctype_iofn);
ctype_status c_ioq_nput(ctype_ioq *, char *, usize);
void *c_ioq_peek(ctype_ioq *);
ctype_status c_ioq_put(ctype_ioq *, char *);
ctype_status c_ioq_putfd(ctype_ioq *, ctype_fd, usize);
ctype_status c_ioq_putfile(ctype_ioq *, char *);
void c_ioq_seek(ctype_ioq *, usize);
ctype_status c_ioq_set(ctype_ioq *, uint);
size c_ioq_vfmt(ctype_ioq *, char *, va_list);

/* mem routines */
void *c_mem_ccpy(void *, usize, void *, int);
void *c_mem_chr(void *, usize, int);
int c_mem_cmp(void *, usize, void *);
void *c_mem_cpy(void *, usize, void *);
int c_mem_equal(void *, usize, void *);
void *c_mem_mem(void *, usize, void *, usize);
void *c_mem_rchr(void *, usize, int);
void *c_mem_set(void *, usize, int);

/* rand routines */
char *c_rand_genseed(char *, usize);
char *c_rand_data(char *, usize);
char *c_rand_name(char *, usize);
u32int c_rand_u32int(u32int);

/* std routines */
void c_std_abort(void);
void *c_std_alloc(usize, usize);
size c_std_allrw(ctype_iofn, ctype_fd, void *, usize);
void *c_std_bsearch(void *, void *, usize, usize, ctype_cmpfn);
void *c_std_calloc(usize, usize);
void c_std_errstr(char *, usize);
void c_std_exit(int);
ctype_status c_std_fdcat(ctype_fd, ctype_fd);
usize c_std_fmtnil(char *, ...);
void *c_std_free_(void *);
char *c_std_getenv(char *);
char *c_std_getsyserr(void);
int c_std_isatty(int);
ctype_fd c_std_mktemp(char *, usize, int, uint);
void *c_std_realloc(void *, usize, usize);
void c_std_setalloc(ctype_allocfn);
void c_std_sort(void *, usize, usize, ctype_cmpfn);
char *c_std_strerror(int, char *, usize);
uvlong c_std_strtouvl(char *, int, uvlong, uvlong, char **, int *);
vlong c_std_strtovl(char *, int, vlong, vlong, char **, int *);
vlong c_std_syscall_(vlong, ...);
long c_std_sysconf(int);
void c_std_werrstr(char *, ...);

/* str routines */
char *c_str_chr(char *, usize, int);
int c_str_cmp(char *, usize, char *);
char *c_str_dup(char *, usize);
usize c_str_len(char *, usize);
char *c_str_rchr(char *, usize, int);
char *c_str_str(char *, usize, char *);

/* sys routines */
ctype_status c_sys_chdir(char *);
ctype_status c_sys_chmod(char *, uint);
ctype_status c_sys_chown(char *, ctype_id, ctype_id);
ctype_status c_sys_close(int);
ctype_status c_sys_dup(ctype_fd, ctype_fd);
ctype_status c_sys_exec(char *, char **, char **);
void c_sys_exit(int);
ctype_status c_sys_fchdir(ctype_fd);
ctype_status c_sys_fchmod(int, uint);
ctype_status c_sys_fchown(ctype_fd, ctype_id, ctype_id);
ctype_id c_sys_fork(void);
ctype_status c_sys_fstat(ctype_stat *, ctype_fd);
char *c_sys_getcwd(char *, usize);
ctype_id c_sys_getgid(void);
ctype_id c_sys_getpid(void);
ctype_id c_sys_getuid(void);
ctype_status c_sys_lchown(char *, ctype_id, ctype_id);
ctype_status c_sys_link(char *, char *);
ctype_status c_sys_llink(char *, char *);
ctype_status c_sys_lstat(ctype_stat *, char *);
ctype_status c_sys_mkdir(char *, uint);
ctype_status c_sys_mknod(char *, uint, ctype_fsid);
void *c_sys_mmap(void *, usize, int, uint, ctype_fd, ctype_fssize);
ctype_status c_sys_munmap(void *, usize);
ctype_fd c_sys_open(char *, uint, uint);
ctype_status c_sys_pipe(ctype_fd [2]);
size c_sys_read(ctype_fd, void *, usize);
size c_sys_readlink(char *, usize, char *);
ctype_status c_sys_rename(char *, char *);
ctype_status c_sys_rmdir(char *);
ctype_fssize c_sys_seek(ctype_fd, ctype_fssize, int);
ctype_status c_sys_stat(ctype_stat *, char *);
ctype_status c_sys_symlink(char *, char *);
uint c_sys_umask(uint);
ctype_status c_sys_uname(ctype_utsname *);
ctype_status c_sys_unlink(char *);
ctype_id c_sys_wait(int *);
ctype_id c_sys_waitpid(ctype_id, int *, uint);
size c_sys_write(ctype_fd, void *, usize);

/* tai routines */
void c_tai_add(ctype_tai *, ctype_tai *, ctype_tai *);
double c_tai_approx(ctype_tai *);
void c_tai_fromtime(ctype_tai *, ctype_time *);
void c_tai_leapadd(ctype_tai *, int);
int c_tai_leapsub(ctype_tai *);
int c_tai_less(ctype_tai *, ctype_tai *);
void c_tai_pack(char *, ctype_tai *);
void c_tai_now(ctype_tai *);
void c_tai_sub(ctype_tai *, ctype_tai *, ctype_tai *);
void c_tai_unpack(char *, ctype_tai *);

/* taia routines */
void c_taia_add(ctype_taia *, ctype_taia *, ctype_taia *);
double c_taia_approx(ctype_taia *);
double c_taia_frac(ctype_taia *);
void c_taia_fromtime(ctype_taia *, ctype_time *);
void c_taia_half(ctype_taia *, ctype_taia *);
int c_taia_less(ctype_taia *, ctype_taia *);
void c_taia_now(ctype_taia *);
void c_taia_pack(char *, ctype_taia *);
void c_taia_sub(ctype_taia *, ctype_taia *, ctype_taia *);
void c_taia_tai(ctype_taia *, ctype_tai *);
void c_taia_unpack(char *, ctype_taia *);

/* uint routines */
char *c_uint_16bigpack(char *, u16int);
u16int c_uint_16bigunpack(char *);
char *c_uint_16pack(char *, u16int);
u16int c_uint_16unpack(char *);
char *c_uint_32bigpack(char *, u32int);
u32int c_uint_32bigunpack(char *);
char *c_uint_32pack(char *, u32int);
u32int c_uint_32unpack(char *);
char *c_uint_64bigpack(char *, u64int);
u64int c_uint_64bigunpack(char *);
char *c_uint_64pack(char *, u64int);
u64int c_uint_64unpack(char *);

/* utf8 routines */
int c_utf8_charntorune(ctype_rune *, char *, usize);
int c_utf8_chartorune(ctype_rune *, char *);
ctype_status c_utf8_checkrune(ctype_rune);
int c_utf8_fullrune(char *, usize);
int c_utf8_isalnum(ctype_rune);
int c_utf8_isalpha(ctype_rune);
int c_utf8_isblank(ctype_rune);
int c_utf8_iscntrl(ctype_rune);
int c_utf8_isdigit(ctype_rune);
int c_utf8_isgraph(ctype_rune);
int c_utf8_islower(ctype_rune);
int c_utf8_isprint(ctype_rune);
int c_utf8_ispunct(ctype_rune);
int c_utf8_isspace(ctype_rune);
int c_utf8_istitle(ctype_rune);
int c_utf8_isupper(ctype_rune);
int c_utf8_isxdigit(ctype_rune);
int c_utf8_runelen(ctype_rune);
usize c_utf8_runenlen(ctype_rune *, usize);
int c_utf8_runetochar(char *, ctype_rune *);
usize c_utf8_utflen(char *);
usize c_utf8_utfnlen(char *, usize);
char *c_utf8_utfrrune(char *, ctype_rune);
char *c_utf8_utfrune(char *, ctype_rune);

/* arr variables */
extern ctype_arr *arr_zero;

/* hsh variables */
extern ctype_hmd *c_hsh_crc32b;
extern ctype_hmd *c_hsh_crc32p;
extern ctype_hmd *c_hsh_djb;
extern ctype_hmd *c_hsh_edf;
extern ctype_hmd *c_hsh_fletcher32;
extern ctype_hmd *c_hsh_md5;
extern ctype_hmd *c_hsh_sha1;
extern ctype_hmd *c_hsh_sha256;
extern ctype_hmd *c_hsh_sha512;
extern ctype_hmd *c_hsh_whirlpool;

/* ioq variables */
extern ctype_ioq *ioq0;
extern ctype_ioq *ioq1;
extern ctype_ioq *ioq2;

/* std variables */
extern char *argv0;
extern char **environ;

/* sys variables */
extern int errno;
