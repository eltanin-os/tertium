include config.mk

.SUFFIXES:
.SUFFIXES: .o .c .s

INC= -I inc -I inc/$(OBJTYPE) -I oss/$(OSNAME)/$(OBJTYPE)

HDR=\
	inc/tertium/std.h\
	oss/$(OSNAME)/$(OBJTYPE)/tertium/cpu.h

# LIB SOURCE
LIBCSRC=\
	src/arr/avail.c\
	src/arr/bget.c\
	src/arr/bytes.c\
	src/arr/cat.c\
	src/arr/cats.c\
	src/arr/fmt.c\
	src/arr/get.c\
	src/arr/init.c\
	src/arr/len.c\
	src/arr/trunc.c\
	src/arr/vfmt.c\
	src/dir/close.c\
	src/dir/hist.c\
	src/dir/open.c\
	src/dir/read.c\
	src/dst/lfree.c\
	src/dst/lnew.c\
	src/dst/lpop.c\
	src/dst/lpush.c\
	src/dst/lsort.c\
	src/dst/qinit.c\
	src/dst/qpop.c\
	src/dst/qpops.c\
	src/dst/qpush.c\
	src/dyn/alloc.c\
	src/dyn/cat.c\
	src/dyn/cats.c\
	src/dyn/fmt.c\
	src/dyn/free.c\
	src/dyn/vfmt.c\
	src/err/die.c\
	src/err/diex.c\
	src/err/vdie.c\
	src/err/vdiex.c\
	src/err/vwarn.c\
	src/err/vwarnx.c\
	src/err/warn.c\
	src/err/warnx.c\
	src/exc/run.c\
	src/exc/runenv.c\
	src/exc/setenv.c\
	src/fmt/fdflush.c\
	src/fmt/fdinit.c\
	src/fmt/fmt.c\
	src/fmt/install.c\
	src/fmt/verb.c\
	src/gen/basename.c\
	src/gen/dirname.c\
	src/hsh/all.c\
	src/hsh/crc32b.c\
	src/hsh/crc32p.c\
	src/hsh/edf.c\
	src/hsh/fletcher16.c\
	src/hsh/putfd.c\
	src/hsh/putfile.c\
	src/ioq/feed.c\
	src/ioq/flush.c\
	src/ioq/fmt.c\
	src/ioq/get.c\
	src/ioq/getln.c\
	src/ioq/init.c\
	src/ioq/nput.c\
	src/ioq/peek.c\
	src/ioq/put.c\
	src/ioq/putfd.c\
	src/ioq/putfile.c\
	src/ioq/seek.c\
	src/ioq/stderr.c\
	src/ioq/stdin.c\
	src/ioq/stdout.c\
	src/ioq/vfmt.c\
	src/mem/ccpy.c\
	src/mem/chr.c\
	src/mem/cmp.c\
	src/mem/cpy.c\
	src/mem/equal.c\
	src/mem/mem.c\
	src/mem/rchr.c\
	src/mem/set.c\
	src/std/argv0.c\
	src/std/alloc.c\
	src/std/bsearch.c\
	src/std/calloc.c\
	src/std/exit.c\
	src/std/free.c\
	src/std/pubrealloc.c\
	src/std/realloc.c\
	src/std/sort.c\
	src/std/strtovl.c\
	src/str/chr.c\
	src/str/cmp.c\
	src/str/len.c\
	src/str/str.c\
	src/sys/abort.c\
	src/sys/allrw.c\
	src/sys/call.c\
	src/sys/chdir.c\
	src/sys/close.c\
	src/sys/conf.c\
	src/sys/dup.c\
	src/sys/errstr.c\
	src/sys/exec.c\
	src/sys/exit.c\
	src/sys/fchdir.c\
	src/sys/fstat.c\
	src/sys/getcwd.c\
	src/sys/getenv.c\
	src/sys/getgid.c\
	src/sys/getsyserr.c\
	src/sys/gettime.c\
	src/sys/getuid.c\
	src/sys/link.c\
	src/sys/lstat.c\
	src/sys/mkdir.c\
	src/sys/mmap.c\
	src/sys/munmap.c\
	src/sys/open.c\
	src/sys/read.c\
	src/sys/rmdir.c\
	src/sys/seek.c\
	src/sys/stat.c\
	src/sys/strerror.c\
	src/sys/unlink.c\
	src/sys/werrstr.c\
	src/sys/write.c\
	src/tai/add.c\
	src/tai/approx.c\
	src/tai/less.c\
	src/tai/now.c\
	src/tai/pack.c\
	src/tai/sub.c\
	src/tai/unpack.c\
	src/tna/add.c\
	src/tna/approx.c\
	src/tna/frac.c\
	src/tna/half.c\
	src/tna/less.c\
	src/tna/now.c\
	src/tna/pack.c\
	src/tna/sub.c\
	src/tna/tai.c\
	src/tna/unpack.c

ASMSRC=\
	oss/$(OSNAME)/$(OBJTYPE)/syscall.s

# LIB PATH
LIBC= lib/libtertium.a

# LIB OBJS
LIBCOBJ= $(LIBCSRC:.c=.o) $(ASMSRC:.s=.o)

# ALL
LIB= $(LIBC)
OBJ= $(LIBCOBJ)

# VAR RULES
all: $(LIB)

$(OBJ): $(HDR) config.mk

# SUFFIX RULES
.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INC) -o $@ -c $<

.s.o:
	$(CC) $(CPPFLAGS) $(INC) -o $@ -c $<

# LIBRARIES RULES
# 'ar' is retarded and cannot update an object with same name
# correctly, so just create the entire library everytime
$(LIBC): $(LIBCOBJ)
	@rm -f $@
	$(AR) rc $@ $(LIBCOBJ)
	$(RANLIB) $@

# USER ACTIONS
clean:
	rm -f $(BIN) $(OBJ) $(LIB)

.PHONY:
	all install clean
