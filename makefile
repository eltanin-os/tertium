.SUFFIXES:
.SUFFIXES: .o .c .s

OSNAME ?= $(shell uname -s | tr "[A-Z]" "[a-z")
OBJTYPE ?= $(shell uname -m)

DESTDIR ?=
PREFIX ?= /usr/local
INCDIR ?= /include
LIBDIR ?= /lib
MANDIR ?= /man

CC ?= cc
CFLAGS ?= -O0 -g -std=c99 -Wall -Wextra -pedantic
AR ?= ar
RANLIB ?= ranlib

HDR=\
	inc/tertium/cpu.h\
	inc/tertium/dat.h\
	inc/tertium/fns.h\
	inc/tertium/std.h

INHDR=\
	macros.h.in\
	ctypes.h.in\
	types.h.in\
	prototypes.h.in

SYSHDR=\
	sys/$(OSNAME)/generic/macros.h.in\
	sys/$(OSNAME)/generic/ctypes.h.in\
	sys/$(OSNAME)/generic/types.h.in\
	sys/$(OSNAME)/generic/prototypes.h.in\
	sys/$(OSNAME)/$(OBJTYPE)/macros.h.in\
	sys/$(OSNAME)/$(OBJTYPE)/ctypes.h.in\
	sys/$(OSNAME)/$(OBJTYPE)/types.h.in\
	sys/$(OSNAME)/$(OBJTYPE)/prototypes.h.in

SYSCALLIN=\
	sys/$(OSNAME)/generic/syscalls.in\
	sys/$(OSNAME)/$(OBJTYPE)/syscalls.in

LIBTERTIUM= lib/libtertium.a
LIBTERTIUMSRC=\
	src/adt/kvadd.c\
	src/adt/kvdel.c\
	src/adt/kvfree.c\
	src/adt/kvget.c\
	src/adt/kvtraverse.c\
	src/adt/lfree.c\
	src/adt/lnew.c\
	src/adt/lpop.c\
	src/adt/lpush.c\
	src/adt/lsort.c\
	src/adt/ltpop.c\
	src/adt/ltpush.c\
	src/arr/avail.c\
	src/arr/bytes.c\
	src/arr/cat.c\
	src/arr/data.c\
	src/arr/fmt.c\
	src/arr/get.c\
	src/arr/idxcat.c\
	src/arr/init.c\
	src/arr/len.c\
	src/arr/ready.c\
	src/arr/tofrom.c\
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
	src/dyn/idxcat.c\
	src/dyn/ready.c\
	src/dyn/shrink.c\
	src/dyn/tofrom.c\
	src/dyn/vfmt.c\
	src/err/die.c\
	src/err/diex.c\
	src/err/vdie.c\
	src/err/vdiex.c\
	src/err/vwarn.c\
	src/err/vwarnx.c\
	src/err/warn.c\
	src/err/warnx.c\
	src/exc/arglist.c\
	src/exc/run.c\
	src/exc/runenv.c\
	src/exc/setenv.c\
	src/exc/spawn0.c\
	src/exc/spawn1.c\
	src/exc/varglist.c\
	src/exc/wait.c\
	src/fmt/fmt.c\
	src/fmt/init.c\
	src/fmt/install.c\
	src/fmt/nput.c\
	src/fmt/print.c\
	src/fmt/put.c\
	src/fmt/verb.c\
	src/fmt/vprint.c\
	src/gen/basename.c\
	src/gen/dirname.c\
	src/hsh/crc32b.c\
	src/hsh/crc32p.c\
	src/hsh/fletcher32.c\
	src/hsh/halfsiphash.c\
	src/hsh/initk.c\
	src/hsh/md5.c\
	src/hsh/murmur32.c\
	src/hsh/octets.c\
	src/hsh/putfd.c\
	src/hsh/putfile.c\
	src/hsh/rol32.c\
	src/hsh/rol64.c\
	src/hsh/ror32.c\
	src/hsh/ror64.c\
	src/hsh/sha1.c\
	src/hsh/sha256.c\
	src/hsh/sha512.c\
	src/hsh/siphash.c\
	src/hsh/str.c\
	src/hsh/update.c\
	src/hsh/whirlpool.c\
	src/ioq/alloc.c\
	src/ioq/feed.c\
	src/ioq/fileno.c\
	src/ioq/flush.c\
	src/ioq/fmt.c\
	src/ioq/get.c\
	src/ioq/getdelim.c\
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
	src/ioq/tofrom.c\
	src/ioq/vfmt.c\
	src/mem/ccpy.c\
	src/mem/chr.c\
	src/mem/cmp.c\
	src/mem/cpy.c\
	src/mem/equal.c\
	src/mem/mem.c\
	src/mem/rchr.c\
	src/mem/set.c\
	src/nix/allrw.c\
	src/nix/chdir.c\
	src/nix/chmod.c\
	src/nix/chown.c\
	src/nix/deepsleep.c\
	src/nix/fdcat.c\
	src/nix/fdchdir.c\
	src/nix/fdchmod.c\
	src/nix/fdchown.c\
	src/nix/fdclose.c\
	src/nix/fdcopy.c\
	src/nix/fdmove.c\
	src/nix/fdopen2.c\
	src/nix/fdopen3.c\
	src/nix/fdset.c\
	src/nix/fdunset.c\
	src/nix/fdwrite.c\
	src/nix/fork.c\
	src/nix/fscopy.c\
	src/nix/fstat.c\
	src/nix/getcwd.c\
	src/nix/gettime.c\
	src/nix/getumask.c\
	src/nix/iopause.c\
	src/nix/lchown.c\
	src/nix/link.c\
	src/nix/lstat.c\
	src/nix/mkdir.c\
	src/nix/mklntemp.c\
	src/nix/mkpath.c\
	src/nix/mktemp.c\
	src/nix/mktemp3.c\
	src/nix/mktemp4.c\
	src/nix/mktemp5.c\
	src/nix/mmap.c\
	src/nix/monotonetime.c\
	src/nix/munmap.c\
	src/nix/pipe.c\
	src/nix/pipe2.c\
	src/nix/read.c\
	src/nix/readlink.c\
	src/nix/rename.c\
	src/nix/rmdir.c\
	src/nix/rmpath.c\
	src/nix/seek.c\
	src/nix/stat.c\
	src/nix/strtomode.c\
	src/nix/symlink.c\
	src/nix/syscall.c\
	src/nix/umask.c\
	src/nix/uname.c\
	src/nix/unlink.c\
	src/nix/waitpid.c\
	src/rand/data.c\
	src/rand/datainc.c\
	src/rand/genseed.c\
	src/rand/name.c\
	src/rand/nameinc.c\
	src/rand/setseed.c\
	src/rand/u32.c\
	src/rand/u32inc.c\
	src/std/alloc.c\
	src/std/argmain.c\
	src/std/argv0.c\
	src/std/atexit.c\
	src/std/bsearch.c\
	src/std/calloc.c\
	src/std/errno.c\
	src/std/errstr.c\
	src/std/exit.c\
	src/std/free.c\
	src/std/getenv.c\
	src/std/getopt.c\
	src/std/getsyserr.c\
	src/std/nbsearch.c\
	src/std/noopt.c\
	src/std/pubrealloc.c\
	src/std/realloc.c\
	src/std/setalloc.c\
	src/std/sort.c\
	src/std/strerror.c\
	src/std/strtouvl.c\
	src/std/strtovl.c\
	src/std/sysconf.c\
	src/std/vtoptr.c\
	src/std/werrstr.c\
	src/str/casechr.c\
	src/str/casecmp.c\
	src/str/caserchr.c\
	src/str/casestr.c\
	src/str/chr.c\
	src/str/cmp.c\
	src/str/cpy.c\
	src/str/cspn.c\
	src/str/dup.c\
	src/str/fmt.c\
	src/str/fmtcnt.c\
	src/str/len.c\
	src/str/ltrim.c\
	src/str/rchr.c\
	src/str/rtrim.c\
	src/str/spn.c\
	src/str/str.c\
	src/str/trim.c\
	src/str/vfmt.c\
	src/str/vfmtcnt.c\
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
	src/tai/u64.c\
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
	src/taia/u64.c\
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

MANPAGES=\
	man/c_mem_cmp.3\
	man/c_dyn_free.3\
	man/c_arr_cat.3\
	man/c_arr_total.3\
	man/c_dyn_cat.3\
	man/c_mem_chr.3\
	man/c_mem_set.3\
	man/c_arr_vfmt.3\
	man/c_arr_fmt.3\
	man/c_arr_avail.3\
	man/c_arr_init.3\
	man/c_mem_cpy.3\
	man/c_mem_mem.3\
	man/c_mem_rchr.3\
	man/c_dyn_ready.3\
	man/c_dyn_shrink.3\
	man/c_mem_equal.3\
	man/c_arr_trunc.3\
	man/c_dyn_alloc.3\
	man/c_dyn_fmt.3\
	man/c_arr_len.3\
	man/c_dyn_vfmt.3\
	man/c_mem_ccpy.3\
	man/c_arr_data.3\
	man/c_arr_bytes.3\
	man/c_arr_get.3

LIBTERTIUMOBJ = $(LIBTERTIUMSRC:.c=.o)

.PHONY: all install clean

all: $(LIBTERTIUM)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -I inc -o $@ -c $<

.s.o:
	$(CC) -o $@ -c $<

src/sys: src/sys.awk $(SYSCALLIN)
	rm -Rf $@
	mkdir $@
	cat $(SYSCALLIN) | (cd $@ && awk -f ../sys.awk)

inc/tertium/cpu.h: inc/tertium/cpu.h.awk $(SYSHDR) $(SYSCALLIN)
	for i in $(INHDR); do cat sys/$(OSNAME)/$(OBJTYPE)/$${i} sys/$(OSNAME)/generic/$${i}; done > $@
	cat sys/$(OSNAME)/$(OBJTYPE)/syscalls.in sys/$(OSNAME)/generic/syscalls.in | awk -f inc/tertium/cpu.h.awk >> $@

$(LIBTERTIUMOBJ): $(HDR) src/sys

SYSCSRC = $(shell find src/sys -name "*.c")
SYSASRC = $(shell find sys/$(OSNAME)/$(OBJTYPE) -name "*.s")
SYSOBJ = $(SYSCSRC:.c=.o) $(SYSASRC:.s=.o)

$(LIBTERTIUM): $(LIBTERTIUMOBJ) $(SYSOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

install: all
	install -dm 755 "$(DESTDIR)$(PREFIX)$(INCDIR)/tertium"
	install -dm 755 "$(DESTDIR)$(PREFIX)$(LIBDIR)"
	install -dm 755 "$(DESTDIR)$(PREFIX)$(MANDIR)/man3"
	install -cm 644 $(MANPAGES) "$(DESTDIR)$(PREFIX)/$(MANDIR)/man3"
	install -cm 644 $(HDR) "$(DESTDIR)$(PREFIX)$(INCDIR)/tertium"
	install -cm 644 lib/libtertium.a "$(DESTDIR)$(PREFIX)$(LIBDIR)"

clean:
	rm -Rf src/sys
	rm -f inc/tertium/cpu.h $(LIBTERTIUM) $(LIBTERTIUMOBJ) $(SYSOBJ)
