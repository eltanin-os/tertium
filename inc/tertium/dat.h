/*
 * MACROS
 */

/* arr macros */
#define c_arr_INIT(a) { sizeof((a)), 0, (a) }

/* dir macros */
enum {
	/* instr */
	C_DIR_FSAGN = 1,
	C_DIR_FSFLW = 2,
	C_DIR_FSSKP = 3,

	/* opts */
	C_DIR_FSLOG = 1 << 0,
	C_DIR_FSPHY = 1 << 1,
	C_DIR_FSCOM = 1 << 2,
	C_DIR_FSNOI = 1 << 3,
	C_DIR_FSVDT = 1 << 4,
	C_DIR_FSXDV = 1 << 5,
	C_DIR_FSDRL = 1 << 6,
	C_DIR_FSFHT = 1 << 7,
	C_DIR_FSSTP = 1 << 8,

	/* types */
	C_DIR_FSD = 1,
	C_DIR_FSDC = 2,
	C_DIR_FSDEF = 3,
	C_DIR_FSDNR = 4,
	C_DIR_FSDOT = 5,
	C_DIR_FSDP = 6,
	C_DIR_FSERR = 7,
	C_DIR_FSF = 8,
	C_DIR_FSFC = 9,
	C_DIR_FSNS = 10,
	C_DIR_FSSL = 11,
	C_DIR_FSSLN = 12,
	C_DIR_FSINT = 13,
};

/* dyn macros */
#define C_DYN_MINSIZ 64

/* exc macros */
#define c_exc_arglist(...) c_exc_arglist_(__VA_ARGS__, nil)

/* fmt macros */
enum {
	C_FMT_OWIDTH = 1 << 0,
	C_FMT_OLEFT = 1 << 1,
	C_FMT_OPREC = 1 << 2,
	C_FMT_OSHARP = 1 << 3,
	C_FMT_OSPACE = 1 << 4,
	C_FMT_OSIGN = 1 << 5,
	C_FMT_OZERO = 1 << 6,
	C_FMT_OUNSIGNED = 1 << 7,
	C_FMT_OSHORT = 1 << 8,
	C_FMT_OLONG = 1 << 9,
	C_FMT_OVLONG = 1 << 10,
	C_FMT_OCOMMA = 1 << 11,
	C_FMT_OBYTE = 1 << 12,
	C_FMT_OFLAG = 1 << 13,
};

/* hsh macros */
enum {
	C_HSH_H32DIG = 4,
	C_HSH_SIPHASHDIG = 8,
	C_HSH_MD5DIG = 16,
	C_HSH_SHA1DIG = 20,
	C_HSH_SHA256DIG = 32,
	C_HSH_SHA512DIG = 64,
	C_HSH_WHIRLPOOLDIG = 64,
};

/* ioq macros */
enum {
	/* default file descriptors */
	C_IOQ_FD0 = 0,
	C_IOQ_FD1 = 1,
	C_IOQ_FD2 = 2,

	/* sizes */
	C_IOQ_BSIZ = 8192,
	C_IOQ_SMALLBSIZ = 512,
	C_IOQ_ERRSIZ = 512,

	/* flags */
	C_IOQ_ONOFLUSH = 1 << 0,
	C_IOQ_OALL = 1 << 0,
};

#define c_ioq_INIT(a, b, c) { { sizeof((b)), 0, (b) }, (c), (a) }

/* std macros */
#define c_std_free(a) a = c_std_free_((a))
#define c_std_getprogname( ) argv0
#define c_std_offsetof(a, b) (ulong)(&(((a *)0)->b))
#define c_std_setprogname(a) argv0 = (a)
#define c_std_vtoptr(...) c_std_vtoptr_(__VA_ARGS__, nil)

#define C_STD_MIN(a, b) (((a) > (b)) ? (b) : (a))
#define C_STD_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define C_STD_NELEM(a)  (sizeof((a))/sizeof((a)[0]))

#define C_STD_ISDOT(a)  ((a)[0]=='.' && ((a)[1]==0 || ((a)[1]=='.' && (a)[2]==0)))
#define C_STD_ISDASH(a) ((a)[0]=='-' && (a)[1]=='\0')

#define C_STD_OVERFLOWM(a, b, c) ((b) && (c) > (((a)-1)/(b)))
#define C_STD_OVERFLOWA(a, b, c) ((c) > (((a)-1)-(b)))

#define C_STD_HOWMANY(a, b) (((a)+((b)-1))/(b))

/* str macros */
#define C_STR_SCMP(a, b) c_mem_cmp((a), sizeof((a)), (b))
#define C_STR_CMP(a, b) c_mem_cmp((a), sizeof((a)) - 1, (b))

/* nix macros */
enum {
	C_NIX_OTMPDIR = 1 << 0,
	C_NIX_OTMPANON = 1 << 1,
};

#define c_nix_abort() { while (*(volatile int *)0); }
#define c_nix_syscall(...) c_nix_syscall_(__VA_ARGS__, nil)

/* tai macros */
#define C_TAI_PACK 8

/* taia macros */
#define C_TAIA_PACK 16

/* utf8 macros */
#define C_UTF8_RUNEERROR 0xFFFD
#define C_UTF8_RUNEMAX 0x10FFFF
#define C_UTF8_MAX 6

/*
 *  TYPES
 */

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
typedef struct ctype_kvtree ctype_kvtree;
typedef struct ctype_node ctype_node;

struct ctype_kvtree {
	void *root;
};

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
	void *__p; /* (private) */
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
	void (*end)(ctype_hst *, char *);
};

struct ctype_hst {
	union {
		u32 x32[16];
		u64 x64[8];
	} st;
	uchar buf[128];
	usize curlen;
	usize len;
};

/* ioq types */
typedef struct ctype_ioq ctype_ioq;

struct ctype_ioq {
	ctype_arr arr;
	ctype_iofn op;
	ctype_fd fd;
};

/* cdb types */
typedef struct ctype_cdb ctype_cdb;
typedef struct ctype_cdbmk ctype_cdbmk;

struct ctype_cdb {
	u32 dpos;
	u32 dlen;
	u32 hpos;
	u32 hslots;
	u32 khash;
	u32 kpos;
	u32 loop;
	u32 size;
	ctype_fd fd;
	uchar *map;
};

struct ctype_cdbmk {
	ctype_arr hplist;
	ctype_ioq ioq;
	u32 off;
	ctype_fd fd;
	char buf[C_IOQ_BSIZ];
};

/* rand types */
typedef struct ctype_rst ctype_rst;

struct ctype_rst {
	u64 state;
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
	u64 x;
};

/* taia types */
typedef struct ctype_taia ctype_taia;

struct ctype_taia {
	ctype_tai sec;
	ulong atto;
	ulong nano;
};

/* arr variables */
extern ctype_arr *arrzero;

/* hsh variables */
extern ctype_hmd *c_hsh_crc32b;
extern ctype_hmd *c_hsh_crc32p;
extern ctype_hmd *c_hsh_fletcher32;
extern ctype_hmd *c_hsh_halfsiphash;
extern ctype_hmd *c_hsh_md5;
extern ctype_hmd *c_hsh_murmur32;
extern ctype_hmd *c_hsh_sha1;
extern ctype_hmd *c_hsh_sha256;
extern ctype_hmd *c_hsh_sha512;
extern ctype_hmd *c_hsh_siphash;
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
