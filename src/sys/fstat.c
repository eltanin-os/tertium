#include <tertium/cpu.h>
#include <tertium/std.h>

int
c_sys_fstat(Stat *p, int f)
{
	__fb_stat st;
	if (c_sys_call(__NR_fstat, f, &st) < 0)
		return -1;
	p->st_size = st.st_size;
	p->st_blksize = st.st_blksize;
	p->st_blocks = st.st_blocks;
	p->st_atim.tv_sec = st.st_atim.tv_sec;
	p->st_atim.tv_nsec = st.st_atim.tv_nsec;
	p->st_ctim.tv_sec = st.st_ctim.tv_sec;
	p->st_ctim.tv_nsec = st.st_ctim.tv_nsec;
	p->st_mtim.tv_sec = st.st_mtim.tv_sec;
	p->st_mtim.tv_nsec = st.st_mtim.tv_nsec;
	p->st_gid = st.st_gid;
	p->st_nlink = st.st_nlink;
	p->st_uid = st.st_uid;
	p->st_dev = st.st_dev;
	p->st_ino = st.st_ino;
	p->st_mode = st.st_mode;
	p->st_rdev = st.st_rdev;
	return 0;
}
