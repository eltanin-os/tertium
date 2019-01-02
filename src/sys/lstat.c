#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_lstat(Stat *p, char *s)
{
	__fb_stat st;
	if (c_sys_call(__NR_lstat, s, &st) < 0)
		return -1;
	p->st_size = st.st_size;
	p->st_blksize = st.st_blksize;
	p->st_blocks = st.st_blocks;
	p->st_atime = st.st_atim.tv_sec;
	p->st_ctime = st.st_ctim.tv_sec;
	p->st_mtime = st.st_mtim.tv_sec;
	p->st_gid = st.st_gid;
	p->st_nlink = st.st_nlink;
	p->st_uid = st.st_uid;
	p->st_dev = st.st_dev;
	p->st_ino = st.st_ino;
	p->st_mode = st.st_mode;
	p->st_rdev = st.st_rdev;
	return 0;
}
