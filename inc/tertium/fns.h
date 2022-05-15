/* adt routines */
ctype_status c_adt_kvadd(ctype_kvtree *, char *, void *);
ctype_status c_adt_kvdel(ctype_kvtree *, char *);
void c_adt_kvfree(ctype_kvtree *);
void *c_adt_kvget(ctype_kvtree *, char *);
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
ctype_status c_arr_idxcat(ctype_arr *, usize, void *, usize, usize);
void c_arr_init(ctype_arr *, char *, usize);
usize c_arr_len(ctype_arr *, usize);
ctype_status c_arr_ready(ctype_arr *, usize, usize);
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
usize c_cdb_datalen(ctype_cdb *);
usize c_cdb_datapos(ctype_cdb *);
ctype_status c_cdb_find(ctype_cdb *, char *, usize);
ctype_status c_cdb_findnext(ctype_cdb *, char *, usize);
void c_cdb_findstart(ctype_cdb *);
void c_cdb_free(ctype_cdb *);
ctype_status c_cdb_init(ctype_cdb *, ctype_fd);
ctype_status c_cdb_mkadd(ctype_cdbmk *, char *, usize, char *, usize);
ctype_status c_cdb_mkaddbegin(ctype_cdbmk *, usize, usize);
ctype_status c_cdb_mkaddend(ctype_cdbmk *, usize, usize, u64);
ctype_status c_cdb_mkfinish(ctype_cdbmk *);
ctype_status c_cdb_mkstart(ctype_cdbmk *, ctype_fd);
ctype_status c_cdb_read(ctype_cdb *, char *, usize, ctype_fssize);

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
ctype_status c_dyn_idxcat(ctype_arr *, usize, void *, usize, usize);
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
void *c_exc_arglist_(char *, ...);
ctype_status c_exc_run(char *, char **);
ctype_status c_exc_runenv(char *, char **, char **);
ctype_status c_exc_setenv(char *, char *);
ctype_id c_exc_spawn0(char *, char **, char **);
ctype_id c_exc_spawn1(char *, char **, char **, ctype_fd *, int);

/* fmt routines */
void c_fmt_init(ctype_fmt *, void *, ctype_fmtopfn);
size c_fmt_fmt(ctype_fmt *, char *);
ctype_status c_fmt_install(ctype_rune, ctype_fmtfn);
ctype_status c_fmt_nput(ctype_fmt *, char *, usize);
ctype_status c_fmt_print(ctype_fmt *, char *, ...);
ctype_status c_fmt_put(ctype_fmt *, char *);
ctype_status c_fmt_vprint(ctype_fmt *, char *, va_list);

/* gen routines */
char *c_gen_basename(char *);
char *c_gen_dirname(char *);

/* hsh routines */
void c_hsh_initk(ctype_hst *, void *, usize);
usize c_hsh_octets(ctype_hst *);
ctype_status c_hsh_putfd(ctype_hst *, ctype_hmd *, ctype_fd, usize);
ctype_status c_hsh_putfile(ctype_hst *, ctype_hmd *, char *);
u32 c_hsh_rol32(u32, int);
u64 c_hsh_rol64(u64, int);
u32 c_hsh_ror32(u32, int);
u64 c_hsh_ror64(u64, int);
void c_hsh_str(ctype_hmd *, char *, usize, char *);
void c_hsh_update(void (*)(ctype_hst *, char *), int, ctype_hst *, char *, usize);

/* ioq routines */
ctype_ioq *c_ioq_alloc(ctype_fd, usize, ctype_iofn);
size c_ioq_feed(ctype_ioq *);
ctype_fd c_ioq_fileno(ctype_ioq *);
ctype_status c_ioq_flush(ctype_ioq *);
size c_ioq_fmt(ctype_ioq *, char *, ...);
size c_ioq_get(ctype_ioq *, char *, usize);
ctype_status c_ioq_getdelim(ctype_ioq *, ctype_arr *, int);
ctype_status c_ioq_getln(ctype_ioq *, ctype_arr *);
void c_ioq_init(ctype_ioq *, ctype_fd, char *, usize, ctype_iofn);
ctype_status c_ioq_nput(ctype_ioq *, char *, usize);
void *c_ioq_peek(ctype_ioq *);
ctype_status c_ioq_put(ctype_ioq *, char *);
ctype_status c_ioq_putfd(ctype_ioq *, ctype_fd, usize);
ctype_status c_ioq_putfile(ctype_ioq *, char *);
void c_ioq_seek(ctype_ioq *, usize);
size c_ioq_tofrom(ctype_ioq *, ctype_ioq *, usize);
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

/* nix routines */
size c_nix_allrw(ctype_iofn, ctype_fd, void *, usize);
ctype_status c_nix_chdir(char *);
ctype_status c_nix_chmod(char *, uint);
ctype_status c_nix_chown(char *, ctype_id, ctype_id);
void c_nix_deepsleep(ctype_taia *, ctype_taia *);
size c_nix_fdcat(ctype_fd, ctype_fd);
ctype_status c_nix_fdchdir(ctype_fd);
ctype_status c_nix_fdchmod(ctype_fd, uint);
ctype_status c_nix_fdchown(ctype_fd, ctype_id, ctype_id);
void c_nix_fdclose(ctype_fd);
ctype_status c_nix_fdcopy(ctype_fd, ctype_fd);
ctype_status c_nix_fdmove(ctype_fd, ctype_fd);
ctype_fd c_nix_fdopen2(char *, uint);
ctype_fd c_nix_fdopen3(char *, uint, uint);
ctype_status c_nix_fdset(ctype_fd, uint);
ctype_status c_nix_fdunset(ctype_fd, uint);
size c_nix_fdwrite(ctype_fd, void *, usize);
ctype_id c_nix_fork(void);
ctype_status c_nix_fdstat(ctype_stat *, ctype_fd);
char *c_nix_getcwd(char *, usize);
void c_nix_gettime(ctype_time *);
uint c_nix_getumask(void);
ctype_status c_nix_iopause(ctype_iopause *, uint, ctype_taia *, ctype_taia *);
ctype_status c_nix_lchown(char *, ctype_id, ctype_id);
ctype_status c_nix_link(char *, char *);
ctype_status c_nix_lstat(ctype_stat *, char *);
ctype_status c_nix_mkdir(char *, uint);
ctype_status c_nix_mkpath(char *, uint, uint);
ctype_fd c_nix_mktemp(char *, usize, uint);
void *c_nix_mmap(void *, usize, int, uint, ctype_fd, ctype_fssize);
void c_nix_monotonetime(ctype_time *);
void c_nix_munmap(void *, usize);
ctype_status c_nix_pipe(ctype_fd *);
ctype_status c_nix_pipe2(ctype_fd *, uint);
size c_nix_fdread(ctype_fd, void *, usize);
size c_nix_readlink(char *, usize, char *);
ctype_status c_nix_rename(char *, char *);
ctype_status c_nix_rmdir(char *);
ctype_status c_nix_rmpath(char *);
ctype_status c_nix_seek(ctype_fd, ctype_fssize, int);
ctype_status c_nix_stat(ctype_stat *, char *);
uint c_nix_strtomode(char *, uint, uint);
ctype_status c_nix_symlink(char *, char *);
vlong c_nix_syscall_(vlong num, ...);
uint c_nix_umask(uint);
ctype_status c_nix_uname(ctype_utsname *);
ctype_status c_nix_unlink(char *);
ctype_id c_nix_waitpid(ctype_id, int *, uint);

/* rand routines */
void c_rand_genseed(ctype_rst *p);
char *c_rand_data(char *, usize);
char *c_rand_datainc(ctype_rst *, char *, usize);
char *c_rand_name(char *, usize);
char *c_rand_nameinc(ctype_rst *, char *, usize);
void c_rand_setseed(ctype_rst *, u64);
u32 c_rand_u32(u32);
u32 c_rand_u32inc(ctype_rst *, u32);

/* std routines */
void *c_std_alloc(usize, usize);
void *c_std_bsearch(void *, void *, usize, usize, ctype_cmpfn);
void *c_std_calloc(usize, usize);
void c_std_errstr(char *, usize);
void c_std_exit(int);
usize c_std_fmtnil(char *, ...);
void *c_std_free_(void *);
char *c_std_getenv(char *);
int c_std_getopt(ctype_arg *, int, char **, char *);
char *c_std_getsyserr(void);
void *c_std_nbsearch(void *, void *, usize, usize, ctype_cmpfn);
int c_std_noopt(ctype_arg *, char *);
void *c_std_realloc(void *, usize, usize);
void c_std_setalloc(ctype_allocfn);
void c_std_sort(void *, usize, usize, ctype_cmpfn);
char *c_std_strerror(int, char *, usize);
uvlong c_std_strtouvl(char *, int, uvlong, uvlong, char **, int *);
vlong c_std_strtovl(char *, int, vlong, vlong, char **, int *);
long c_std_sysconf(int);
void *c_std_vtoptr_(char *, ...);
void c_std_werrstr(char *, ...);

/* str routines */
char *c_str_casechr(char *, usize, int);
int c_str_casecmp(char *, usize, char *);
char *c_str_caserchr(char *, usize, int);
char *c_str_casestr(char *, usize, char *);
char *c_str_chr(char *, usize, int);
int c_str_cmp(char *, usize, char *);
char *c_str_cpy(char *, usize, char *);
usize c_str_cspn(char *, usize, char *);
char *c_str_dup(char *, usize);
usize c_str_len(char *, usize);
char *c_str_ltrim(char *, usize, char *);
char *c_str_rchr(char *, usize, int);
char *c_str_rtrim(char *, usize, char *);
usize c_str_spn(char *, usize, char *);
char *c_str_str(char *, usize, char *);
char *c_str_trim(char *, usize, char *);

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
void c_tai_u64(ctype_tai *, u64);
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
void c_taia_u64(ctype_taia *, u64);
void c_taia_unpack(char *, ctype_taia *);

/* uint routines */
char *c_uint_16bigpack(char *, u16);
u16 c_uint_16bigunpack(char *);
char *c_uint_16pack(char *, u16);
u16 c_uint_16unpack(char *);
char *c_uint_32bigpack(char *, u32);
u32 c_uint_32bigunpack(char *);
char *c_uint_32pack(char *, u32);
u32 c_uint_32unpack(char *);
char *c_uint_64bigpack(char *, u64);
u64 c_uint_64bigunpack(char *);
char *c_uint_64pack(char *, u64);
u64 c_uint_64unpack(char *);

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
