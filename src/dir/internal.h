#define BFAIL ((void *)-1)

int _tertium_dir_info(ctype_dir *, ctype_dent *);
ctype_node *_tertium_dir_newfile(char *, char *, uint);
ctype_node *_tertium_dir_builddir(ctype_dir *);
