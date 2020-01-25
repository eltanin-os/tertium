include config.mk

.SUFFIXES:
.SUFFIXES: .o .c .s

INC= -I inc -I oss/$(OSNAME) -I oss/$(OSNAME)/$(OBJTYPE)

HDR=\
	inc/tertium/std.h\
	inc/tertium/cpu.h

# LIB SOURCE
ASMSRC=\
	sys/$(OSNAME)/$(OBJTYPE).s

LIBCSRC=\
	src/adt/lfree.c\
	src/adt/lnew.c\
	src/adt/lpop.c\
	src/adt/lpush.c\
	src/adt/lsort.c\
	src/adt/ltpush.c\
	src/arr/arrzero.c\
	src/arr/avail.c\
	src/arr/bytes.c\
	src/arr/cat.c\
	src/arr/data.c\
	src/arr/fmt.c\
	src/arr/get.c\
	src/arr/init.c\
	src/arr/len.c\
	src/arr/total.c\
	src/arr/trunc.c\
	src/arr/vfmt.c\
	src/cal/datefrommjd.c\
	src/cal/datemjd.c\
	src/cal/datenorm.c\
	src/cal/timetai.c\
	src/cal/timeutc.c\
	src/cdb/datalen.c\
	src/cdb/datapos.c\
	src/cdb/find.c\
	src/cdb/findnext.c\
	src/cdb/findstart.c\
	src/cdb/free.c\
	src/cdb/init.c\
	src/cdb/mkadd.c\
	src/cdb/mkaddbegin.c\
	src/cdb/mkaddend.c\
	src/cdb/mkfinish.c\
	src/cdb/mkstart.c\
	src/cdb/read.c\
	src/dir/builddir.c\
	src/dir/children.c\
	src/dir/close.c\
	src/dir/info.c\
	src/dir/list.c\
	src/dir/newfile.c\
	src/dir/open.c\
	src/dir/read.c\
	src/dir/set.c\
	src/dyn/alloc.c\
	src/dyn/cat.c\
	src/dyn/fmt.c\
	src/dyn/free.c\
	src/dyn/ready.c\
	src/dyn/shrink.c\
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
	src/fmt/fmt.c\
	src/fmt/init.c\
	src/fmt/install.c\
	src/fmt/verb.c\
	src/gen/basename.c\
	src/gen/dirname.c\
	src/hsh/all.c\
	src/hsh/crc32b.c\
	src/hsh/crc32p.c\
	src/hsh/digest.c\
	src/hsh/djb.c\
	src/hsh/edf.c\
	src/hsh/fletcher32.c\
	src/hsh/len.c\
	src/hsh/md5.c\
	src/hsh/putfd.c\
	src/hsh/putfile.c\
	src/hsh/sha1.c\
	src/hsh/sha256.c\
	src/hsh/sha512.c\
	src/hsh/update.c\
	src/hsh/whirlpool.c\
	src/ioq/alloc.c\
	src/ioq/feed.c\
	src/ioq/fileno.c\
	src/ioq/flush.c\
	src/ioq/fmt.c\
	src/ioq/free.c\
	src/ioq/get.c\
	src/ioq/getall.c\
	src/ioq/getdelim.c\
	src/ioq/getln.c\
	src/ioq/init.c\
	src/ioq/nput.c\
	src/ioq/peek.c\
	src/ioq/put.c\
	src/ioq/putfd.c\
	src/ioq/putfile.c\
	src/ioq/seek.c\
	src/ioq/set.c\
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
	src/rand/data.c\
	src/rand/genseed.c\
	src/rand/name.c\
	src/rand/u32int.c\
	src/std/abort.c\
	src/std/alloc.c\
	src/std/allrw.c\
	src/std/argv0.c\
	src/std/bsearch.c\
	src/std/calloc.c\
	src/std/errno.c\
	src/std/errstr.c\
	src/std/exit.c\
	src/std/fdcat.c\
	src/std/fmtnil.c\
	src/std/free.c\
	src/std/getsyserr.c\
	src/std/mktemp.c\
	src/std/pubrealloc.c\
	src/std/realloc.c\
	src/std/setalloc.c\
	src/std/sort.c\
	src/std/strerror.c\
	src/std/strtouvl.c\
	src/std/strtovl.c\
	src/std/syscall.c\
	src/std/werrstr.c\
	src/str/chr.c\
	src/str/cmp.c\
	src/str/dup.c\
	src/str/len.c\
	src/str/rchr.c\
	src/str/str.c\
	src/sys/chdir.c\
	src/sys/chmod.c\
	src/sys/chown.c\
	src/sys/close.c\
	src/sys/conf.c\
	src/sys/dup.c\
	src/sys/exec.c\
	src/sys/exit.c\
	src/sys/fchdir.c\
	src/sys/fchmod.c\
	src/sys/fchown.c\
	src/sys/fork.c\
	src/sys/fstat.c\
	src/sys/getcwd.c\
	src/sys/getenv.c\
	src/sys/getgid.c\
	src/sys/getpid.c\
	src/sys/getuid.c\
	src/sys/isatty.c\
	src/sys/lchown.c\
	src/sys/link.c\
	src/sys/llink.c\
	src/sys/lstat.c\
	src/sys/mkdir.c\
	src/sys/mknod.c\
	src/sys/mmap.c\
	src/sys/munmap.c\
	src/sys/open.c\
	src/sys/pipe.c\
	src/sys/read.c\
	src/sys/readlink.c\
	src/sys/rename.c\
	src/sys/rmdir.c\
	src/sys/seek.c\
	src/sys/stat.c\
	src/sys/symlink.c\
	src/sys/umask.c\
	src/sys/uname.c\
	src/sys/unlink.c\
	src/sys/wait.c\
	src/sys/waitpid.c\
	src/sys/write.c\
	src/tai/add.c\
	src/tai/approx.c\
	src/tai/fromtime.c\
	src/tai/leapadd.c\
	src/tai/leapsub.c\
	src/tai/leaptab.c\
	src/tai/less.c\
	src/tai/now.c\
	src/tai/pack.c\
	src/tai/sub.c\
	src/tai/unpack.c\
	src/taia/add.c\
	src/taia/approx.c\
	src/taia/frac.c\
	src/taia/fromtime.c\
	src/taia/half.c\
	src/taia/less.c\
	src/taia/now.c\
	src/taia/pack.c\
	src/taia/sub.c\
	src/taia/tai.c\
	src/taia/unpack.c\
	src/uint/16bigpack.c\
	src/uint/16bigunpack.c\
	src/uint/16pack.c\
	src/uint/16unpack.c\
	src/uint/32bigpack.c\
	src/uint/32bigunpack.c\
	src/uint/32pack.c\
	src/uint/32unpack.c\
	src/uint/64bigpack.c\
	src/uint/64bigunpack.c\
	src/uint/64pack.c\
	src/uint/64unpack.c\
	src/utf8/charntorune.c\
	src/utf8/chartorune.c\
	src/utf8/checkrune.c\
	src/utf8/fullrune.c\
	src/utf8/isalnum.c\
	src/utf8/isalpha.c\
	src/utf8/isblank.c\
	src/utf8/iscntrl.c\
	src/utf8/isdigit.c\
	src/utf8/isgraph.c\
	src/utf8/islower.c\
	src/utf8/isprint.c\
	src/utf8/ispunct.c\
	src/utf8/isspace.c\
	src/utf8/istitle.c\
	src/utf8/isupper.c\
	src/utf8/isxdigit.c\
	src/utf8/mtab.c\
	src/utf8/runecmp.c\
	src/utf8/runelen.c\
	src/utf8/runenlen.c\
	src/utf8/runetochar.c\
	src/utf8/utflen.c\
	src/utf8/utfnlen.c\
	src/utf8/utfrrune.c\
	src/utf8/utfrune.c

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

# HEADERS RULES
inc/tertium/cpu.h: config.mk sys/$(OSNAME)/common.h.in sys/$(OSNAME)/$(OBJTYPE).h.in
	@cat sys/$(OSNAME)/common.h.in     1> $@
	@echo                              1>> $@
	@cat sys/$(OSNAME)/$(OBJTYPE).h.in 1>> $@

# LIBRARIES RULES
# 'ar' is retarded and cannot update an object with same name
# correctly, so just create the entire library everytime
$(LIBC): $(LIBCOBJ)
	@rm -f $@
	$(AR) rc $@ $(LIBCOBJ)
	$(RANLIB) $@

# USER ACTIONS
install: all
	$(INSTALL) -dm 755 $(DESTDIR)$(INCDIR)/tertium
	$(INSTALL) -dm 755 $(DESTDIR)$(LIBDIR)
	$(INSTALL) -cm 644 $(HDR) $(DESTDIR)$(INCDIR)/tertium
	$(INSTALL) -cm 644 $(LIB) $(DESTDIR)$(LIBDIR)

clean:
	rm -f $(BIN) $(OBJ) $(LIB)
	rm -f inc/tertium/cpu.h

.PHONY:
	all install clean
