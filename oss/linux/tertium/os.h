/* fallback macros */
#define __C_STCOPY(a, b)                    \
{ (a)->st_size = (b).st_size;               \
  (a)->st_blksize = (b).st_blksize;         \
  (a)->st_blocks = (b).st_blocks;           \
  (a)->st_atim.tv_sec = (b).st_atime;       \
  (a)->st_atim.tv_nsec = (b).st_atime_nsec; \
  (a)->st_ctim.tv_sec = (b).st_ctime;       \
  (a)->st_ctim.tv_nsec = (b).st_ctime_nsec; \
  (a)->st_mtim.tv_sec = (b).st_mtime;       \
  (a)->st_mtim.tv_nsec = (b).st_mtime_nsec; \
  (a)->st_gid = (b).st_gid;                 \
  (a)->st_nlink = (b).st_nlink;             \
  (a)->st_uid = (b).st_uid;                 \
  (a)->st_dev = (b).st_dev;                 \
  (a)->st_ino = (b).st_ino;                 \
  (a)->st_mode = (b).st_mode;               \
  (a)->st_rdev = (b).st_rdev; }

/* limits macros */
#define C_NAMEMAX 255
#define C_PATHMAX 4095

#define C_ARGMAX       131072
#define C_CHILDMAX     999
#define C_HOSTNAMEMAX  255
#define C_LOGINNAMEMAX 256
#define C_NGROUPSMAX   32
#define C_OPENMAX      1024  /* !!! */
#define C_PAGESIZE     4096
#define C_SYMLOOPMAX   40    /* !!! */
#define C_TTYNAMEMAX   32    /* !!! */

#define C_CHARBIT   8
#define C_CHARMAX   0x7F
#define C_UCHARMAX  0xFF
#define C_INTMAX    0x7FFFFFFF
#define C_UINTMAX   0xFFFFFFFFU
#define C_LONGMAX   0x7FFFFFFFL
#define C_ULONGMAX  0xFFFFFFFFUL
#define C_SHRTMAX   0x7FFF
#define C_USHRTMAX  0xFFFFU
#define C_SIZEMAX   0x7FFFFFFFL
#define C_USIZEMAX  0xFFFFFFFFUL
#define C_VLONGMAX  0x7FFFFFFFFFFFFFFFLL
#define C_UVLONGMAX 0x7FFFFFFFFFFFFFFFULL
#define C_CHARMIN   (-C_CHARMAX-1)
#define C_INTMIN    (-C_INTMAX-1)
#define C_LONGMIN   (-C_LONGMAX-1)
#define C_SHRTMIN   (-C_SHRTMAX-1)
#define C_SIZEMIN   (-C_SIZEMAX-1)
#define C_VLONGMIN  (-C_VLONGMAX-1)

/* option macros */
#define C_OREAD  0x0
#define C_OWRITE 0x1
#define C_ORDWR  0x2

/* others macros
 * TODO: rename */
#define CLOCK_REALTIME 0
#define MAP_FAILED     ((void *)-1)
#define MAP_SHARED     0x01
#define MAP_PRIVATE    0x02
#define PROT_READ      0x01
#define PROT_WRITE     0x02
#define SEEK_SET       0x00

#define _SC_ARG_MAX        0
#define _SC_CHILD_MAX      1
#define _SC_HOST_NAME_MAX  180
#define _SC_LOGIN_NAME_MAX 71
#define _SC_NGROUPS_MAX    3
#define _SC_OPEN_MAX       4
#define _SC_PAGESIZE       30
#define _SC_SYMLOOP_MAX    173
#define _SC_TTY_NAME_MAX   72
#define _SC_VERSION        29
#define _POSIX_VERSION     200809L

#define AT_FDCWD -100
#define AT_SYMLINK_NOFOLLOW 0x100
#define AT_SYMLINK_FOLLOW   0x400

/* stat macros */
#define C_IFMT  0xF000
#define C_IFBLK 0x6000
#define C_IFCHR 0x2000
#define C_IFDIR 0x4000
#define C_IFIFO 0x1000
#define C_IFLNK 0xA000
#define C_IFREG 0x8000
#define C_IFSCK 0xC000

#define C_ISBLK(a)  (((a) & C_IFBLK) == C_IFBLK)
#define C_ISCHR(a)  (((a) & C_IFCHR) == C_IFCHR)
#define C_ISDIR(a)  (((a) & C_IFDIR) == C_IFDIR)
#define C_ISFIFO(a) (((a) & C_IFIFO) == C_IFIFO)
#define C_ISLNK(a)  (((a) & C_IFLNK) == C_IFLNK)
#define C_ISREG(a)  (((a) & C_IFREG) == C_IFREG)
#define C_ISSCK(a)  (((a) & C_IFSCK) == C_IFSCK)

#define C_ACCESSPERMS (0x1C0|0x038|0x007)
#define C_ALLPERMS    (0x800|0x400|0x200|0x1C0|0x038|0x007)
#define C_DEFFILEMODE (0x100|0x080|0x020|0x010|0x004|0x002)

/* */
long __asm_syscall(long, ...);

