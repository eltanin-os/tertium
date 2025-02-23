# call `make src/sys` first
.SUFFIXES:
.SUFFIXES: .o .c .s

OSNAME ?= $(shell uname -s)
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
	src/adt/lrot.c\
	src/adt/lsort.c\
	src/adt/lswap.c\
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
	src/exc/run.c\
	src/exc/runenv.c\
	src/exc/setenv.c\
	src/exc/spawn0.c\
	src/exc/spawn1.c\
	src/exc/split.c\
	src/exc/vsplit.c\
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
	src/hsh/blake2b.c\
	src/hsh/crc32b.c\
	src/hsh/crc32p.c\
	src/hsh/fletcher32.c\
	src/hsh/halfsiphash.c\
	src/hsh/initk.c\
	src/hsh/md5.c\
	src/hsh/murmur32.c\
	src/hsh/octets.c\
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
	src/nix/fdchdir.c\
	src/nix/fdchmod.c\
	src/nix/fdchown.c\
	src/nix/fdclose.c\
	src/nix/fdcopy.c\
	src/nix/fdfmt.c\
	src/nix/fdmove.c\
	src/nix/fdopen2.c\
	src/nix/fdopen3.c\
	src/nix/fdputfile.c\
	src/nix/fdset.c\
	src/nix/fdunset.c\
	src/nix/fdvfmt.c\
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
	src/nix/mktemp6.c\
	src/nix/mmap.c\
	src/nix/monotonetime.c\
	src/nix/munmap.c\
	src/nix/normalizepath.c\
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
	src/std/nbsearch.c\
	src/std/noopt.c\
	src/std/ptrlist.c\
	src/std/pubrealloc.c\
	src/std/putfd.c\
	src/std/putfile.c\
	src/std/realloc.c\
	src/std/setalloc.c\
	src/std/sort.c\
	src/std/strerror.c\
	src/std/strtouvl.c\
	src/std/strtovl.c\
	src/std/sysconf.c\
	src/std/vptrlist.c\
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
	man/c_adt_kvadd.3\
	man/c_adt_kvdel.3\
	man/c_adt_kvfree.3\
	man/c_adt_kvget.3\
	man/c_adt_kvtraverse.3\
	man/c_adt_lfree.3\
	man/c_adt_lnew.3\
	man/c_adt_lpop.3\
	man/c_adt_lpush.3\
	man/c_adt_lsort.3\
	man/c_adt_ltpop.3\
	man/c_adt_ltpush.3\
	man/c_arr_avail.3\
	man/c_arr_bytes.3\
	man/c_arr_cat.3\
	man/c_arr_data.3\
	man/c_arr_fmt.3\
	man/c_arr_get.3\
	man/c_arr_idxcat.3\
	man/c_arr_init.3\
	man/c_arr_len.3\
	man/c_arr_ready.3\
	man/c_arr_tofrom.3\
	man/c_arr_total.3\
	man/c_arr_trunc.3\
	man/c_arr_vfmt.3\
	man/c_cal_datefrommjd.3\
	man/c_cal_datemjd.3\
	man/c_cal_timetai.3\
	man/c_cal_timeutc.3\
	man/c_cdb_datalen.3\
	man/c_cdb_datapos.3\
	man/c_cdb_find.3\
	man/c_cdb_findnext.3\
	man/c_cdb_findstart.3\
	man/c_cdb_free.3\
	man/c_cdb_init.3\
	man/c_cdb_mkadd.3\
	man/c_cdb_mkfinish.3\
	man/c_cdb_mkstart.3\
	man/c_cdb_read.3\
	man/c_dir_children.3\
	man/c_dir_close.3\
	man/c_dir_list.3\
	man/c_dir_open.3\
	man/c_dir_read.3\
	man/c_dir_set.3\
	man/c_dyn_alloc.3\
	man/c_dyn_cat.3\
	man/c_dyn_fmt.3\
	man/c_dyn_free.3\
	man/c_dyn_idxcat.3\
	man/c_dyn_ready.3\
	man/c_dyn_shrink.3\
	man/c_dyn_tofrom.3\
	man/c_dyn_vfmt.3\
	man/c_err_die.3\
	man/c_err_diex.3\
	man/c_err_vdie.3\
	man/c_err_vdiex.3\
	man/c_err_vwarn.3\
	man/c_err_vwarnx.3\
	man/c_err_warn.3\
	man/c_err_warnx.3\
	man/c_exc_run.3\
	man/c_exc_runenv.3\
	man/c_exc_setenv.3\
	man/c_exc_spawn0.3\
	man/c_exc_spawn1.3\
	man/c_exc_split.3\
	man/c_exc_wait.3\
	man/c_fmt_fmt.3\
	man/c_fmt_init.3\
	man/c_fmt_install.3\
	man/c_fmt_nput.3\
	man/c_fmt_print.3\
	man/c_fmt_put.3\
	man/c_fmt_vprint.3\
	man/c_gen_basename.3\
	man/c_gen_dirname.3\
	man/c_hsh_initk.3\
	man/c_hsh_octets.3\
	man/c_hsh_putfd.3\
	man/c_hsh_putfile.3\
	man/c_hsh_rol32.3\
	man/c_hsh_rol64.3\
	man/c_hsh_ror32.3\
	man/c_hsh_ror64.3\
	man/c_hsh_str.3\
	man/c_ioq_feed.3\
	man/c_ioq_fileno.3\
	man/c_ioq_flush.3\
	man/c_ioq_fmt.3\
	man/c_ioq_get.3\
	man/c_ioq_getdelim.3\
	man/c_ioq_getln.3\
	man/c_ioq_init.3\
	man/c_ioq_nput.3\
	man/c_ioq_peek.3\
	man/c_ioq_put.3\
	man/c_ioq_putfd.3\
	man/c_ioq_putfile.3\
	man/c_ioq_seek.3\
	man/c_ioq_tofrom.3\
	man/c_ioq_vfmt.3\
	man/c_mem_ccpy.3\
	man/c_mem_chr.3\
	man/c_mem_cmp.3\
	man/c_mem_cpy.3\
	man/c_mem_equal.3\
	man/c_mem_mem.3\
	man/c_mem_rchr.3\
	man/c_mem_set.3\
	man/c_nix_allrw.3\
	man/c_nix_deepsleep.3\
	man/c_nix_fdcat.3\
	man/c_nix_fscopy.3\
	man/c_nix_iopause.3\
	man/c_nix_mklntemp.3\
	man/c_nix_mkpath.3\
	man/c_nix_mktemp.3\
	man/c_nix_normalizepath.3\
	man/c_nix_rmpath.3\
	man/c_nix_strtomode.3\
	man/c_rand_data.3\
	man/c_rand_datainc.3\
	man/c_rand_genseed.3\
	man/c_rand_name.3\
	man/c_rand_nameinc.3\
	man/c_rand_setseed.3\
	man/c_rand_u32.3\
	man/c_rand_u32inc.3\
	man/c_std_alloc.3\
	man/c_std_atexit.3\
	man/c_std_bsearch.3\
	man/c_std_calloc.3\
	man/c_std_errstr.3\
	man/c_std_exit.3\
	man/c_std_free.3\
	man/c_std_getenv.3\
	man/c_std_getopt.3\
	man/c_std_nbsearch.3\
	man/c_std_noopt.3\
	man/c_std_ptrlist.3\
	man/c_std_realloc.3\
	man/c_std_setalloc.3\
	man/c_std_sort.3\
	man/c_std_strerror.3\
	man/c_std_strtouvl.3\
	man/c_std_strtovl.3\
	man/c_std_werrstr.3\
	man/c_str_casechr.3\
	man/c_str_casecmp.3\
	man/c_str_caserchr.3\
	man/c_str_casestr.3\
	man/c_str_chr.3\
	man/c_str_cmp.3\
	man/c_str_cpy.3\
	man/c_str_cspn.3\
	man/c_str_dup.3\
	man/c_str_fmt.3\
	man/c_str_fmtcnt.3\
	man/c_str_len.3\
	man/c_str_ltrim.3\
	man/c_str_rchr.3\
	man/c_str_rtrim.3\
	man/c_str_spn.3\
	man/c_str_str.3\
	man/c_str_trim.3\
	man/c_str_vfmt.3\
	man/c_str_vfmtcnt.3\
	man/c_tai_add.3\
	man/c_tai_approx.3\
	man/c_tai_fromtime.3\
	man/c_tai_less.3\
	man/c_tai_now.3\
	man/c_tai_pack.3\
	man/c_tai_sub.3\
	man/c_tai_u64.3\
	man/c_tai_unpack.3\
	man/c_taia_add.3\
	man/c_taia_approx.3\
	man/c_taia_frac.3\
	man/c_taia_fromtime.3\
	man/c_taia_half.3\
	man/c_taia_less.3\
	man/c_taia_now.3\
	man/c_taia_pack.3\
	man/c_taia_sub.3\
	man/c_taia_u64.3\
	man/c_taia_unpack.3\
	man/c_uint_16bigpack.3\
	man/c_uint_16bigunpack.3\
	man/c_uint_16pack.3\
	man/c_uint_16unpack.3\
	man/c_uint_32bigpack.3\
	man/c_uint_32bigunpack.3\
	man/c_uint_32pack.3\
	man/c_uint_32unpack.3\
	man/c_uint_64bigpack.3\
	man/c_uint_64bigunpack.3\
	man/c_uint_64pack.3\
	man/c_uint_64unpack.3\
	man/c_utf8_charntorune.3\
	man/c_utf8_chartorune.3\
	man/c_utf8_checkrune.3\
	man/c_utf8_fullrune.3\
	man/c_utf8_isalnum.3\
	man/c_utf8_isalpha.3\
	man/c_utf8_isblank.3\
	man/c_utf8_iscntrl.3\
	man/c_utf8_isdigit.3\
	man/c_utf8_isgraph.3\
	man/c_utf8_islower.3\
	man/c_utf8_isprint.3\
	man/c_utf8_ispunct.3\
	man/c_utf8_isspace.3\
	man/c_utf8_istitle.3\
	man/c_utf8_isupper.3\
	man/c_utf8_isxdigit.3\
	man/c_utf8_runelen.3\
	man/c_utf8_runenlen.3\
	man/c_utf8_runetochar.3\
	man/c_utf8_utflen.3\
	man/c_utf8_utfnlen.3\
	man/c_utf8_utfrrune.3\
	man/c_utf8_utfrune.3

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
