#include <tertium/cpu.h>
#include <tertium/std.h>

static ctype_status
regcopy(ctype_fd fd, char *s)
{
	ctype_ioq ioq;
	c_ioq_init(&ioq, fd, nil, 0, &c_nix_fdwrite);
	return c_ioq_putfile(&ioq, s);
}

static ctype_status
lncopy(char *dest, ctype_stat *stp, char *s)
{
	size r;
	char buf[C_LIM_PATHMAX];
	if ((r = c_nix_readlink(buf, sizeof(buf), s)) < 0) return -1;
	if ((size)stp->size != r) {
		c_std_werrstr("file changed");
		return -1;
	}
	return c_nix_symlink(dest, buf);
}

static ctype_status
ndcopy(char *s, ctype_stat *stp)
{
	return c_sys_mknod(s, stp->mode, stp->dev);
}

ctype_status
c_nix_fscopy(char *dest, int pflag, char *src, ctype_stat *stp)
{
	ctype_stat st;
	ctype_arr arr;
	ctype_time times[2];
	ctype_fd fd;
	ctype_status r;
	char *s, *tmp;

	fd = -1;
	r = 0;
	if ((c_nix_stat(&st, dest) < 0)) {
		if (errno != C_ERR_ENOENT) return -1;
		r = errno;
	}

	tmp = nil;
	if (C_NIX_ISDIR(st.mode)) {
		if ((r = c_nix_mkpath(dest, 0755, 0755)) < 0) goto done;
		/* build the path */
		c_mem_set(&arr, sizeof(arr), 0);
		if (!(s = c_str_dup(src, -1))) goto done;
		r = c_dyn_fmt(&arr, "%s/%s", dest, c_gen_basename(s));
		c_std_free(s);
		if (r < 0) goto done;
		c_dyn_shrink(&arr);
		tmp = c_arr_data(&arr);
		/* set the tmp directory */
		c_mem_set(&arr, sizeof(arr), 0);
		r = c_dyn_fmt(&arr, "%s/tmpfile.XXXXXXXXX", dest);
		if (r < 0) goto done;
		s = c_arr_data(&arr);
		dest = tmp;
	} else if (r != C_ERR_ENOENT) {
		errno = C_ERR_EEXIST;
		return -1;
	} else {
		if ((st.dev == stp->dev) && (st.ino == stp->ino)) {
			c_std_werrstr("same file");
			return -1;
		}
		c_mem_set(&arr, sizeof(arr), 0);
		if (!(s = c_str_dup(dest, -1))) goto done;
		r = c_nix_mkpath((s = c_gen_dirname(s)), 0755, 0755);
		if (r < 0) {
			c_std_free(s);
			goto done;
		}
		r = c_dyn_fmt(&arr, "%s/tmpfile.XXXXXXXXX", s);
		c_std_free(s);
		if (r < 0) goto done;
		s = c_arr_data(&arr);
	}

	if (C_NIX_ISREG(stp->mode)) {
		r = fd = c_nix_mktemp5(s, c_arr_bytes(&arr), 0, 0, stp->mode);
		if (fd < 0) goto done;
		r = regcopy(fd, src);
		if (pflag) {
			times[0] = stp->atim;
			times[1] = stp->mtim;
			r = c_sys_futimens(fd, times);
			if (r < 0) goto done;
			r = c_nix_fdchown(fd, stp->uid, stp->gid);
			if (r < 0) goto done;
		}
	} else {
		r = fd = c_nix_mktemp3(s, c_arr_bytes(&arr), C_NIX_OTMPANON);
		if (fd < 0) goto done;
		c_nix_fdclose(fd);
		if (C_NIX_ISLNK(stp->mode)) {
			r = lncopy(s, stp, src);
		} else {
			r = ndcopy(s, stp);
		}
		if (pflag) {
			times[0] = stp->atim;
			times[1] = stp->mtim;
			r = c_sys_utimensat(C_NIX_FDCWD,
			    s, times, C_NIX_SLNOFLW);
			if (r < 0) goto done;
		}
		if (C_NIX_ISLNK(stp->mode)) {
			r = c_nix_lchown(s, stp->uid, stp->gid);
		} else {
			r = c_nix_chown(s, stp->uid, stp->gid);
		}
		if (r < 0) goto done;
	}
	r = c_nix_rename(dest, s);
done:
	if (fd < 0) c_nix_fdclose(fd);
	c_std_free(tmp);
	c_dyn_free(&arr);
	return r;
}
