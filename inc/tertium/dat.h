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

/* exc macros */
#define c_exc_arglist(...) c_exc_arglist_(__VA_ARGS__, nil)

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
	C_SMALLBIOSIZ = 512,
	C_ERRSIZ = 512,

	/* flags */
	C_IOQ_ONOFLUSH = 1 << 0,
	__IOQ_OALL = 1 << 0,
};

#define c_ioq_INIT(a, b, c) { { sizeof((b)), 0, (b) }, (c), (a), 0 }

/* std macros */
enum {
	C_OTMPDIR = 1 << 0,
	C_OTMPANON = 1 << 1,
};

#define c_std_free(a) a = c_std_free_((a))
#define c_std_getprogname( ) argv0
#define c_std_offsetof(a, b) (ulong)(&(((a *)0)->b))
#define c_std_setprogname(a) argv0 = (a)
#define c_std_syscall(...) c_std_syscall_(__VA_ARGS__, nil)
#define c_std_vtoptr(...) c_std_vtoptr_(__VA_ARGS__, nil)

#define C_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define C_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define C_NELEM(a)  (sizeof((a))/sizeof((a)[0]))

#define C_ISDOT(a)  ((a)[0]=='.' && ((a)[1]==0 || ((a)[1]=='.' && (a)[2]==0)))
#define C_ISDASH(a) ((a)[0]=='-' && (a)[1]=='\0')

#define C_OFLW_UM(a, b, c) ((b) && (c) > (((a)-1)/(b)))
#define C_OFLW_UA(a, b, c) ((c) > (((a)-1)-(b)))

#define C_HOWMANY(a, b) (((a)+((b)-1))/(b))

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

/* std types */
typedef struct ctype_arg ctype_arg;

struct ctype_arg {
	usize pos;
	int opt;
	int idx;
	char *arg;
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
extern ctype_arg *argmain;
extern char *argv0;
extern char **environ;

/* sys variables */
extern int errno;
