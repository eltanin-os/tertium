INSTALL= /usr/bin/install

PREFIX= /usr/local
MANDIR= $(PREFIX)/share/man
LIBDIR= $(PREFIX)/lib
INCDIR= $(PREFIX)/include

AR     = ar
CC     = cc
RANLIB = ranlib

CFLAGS   = -O0 -g -std=c99 -Wall -Wextra -Werror -pedantic
LDFLAGS  =

# OSes:
# port (system libc)
OSNAME  = port
# Arch:
# port (system libc)
OBJTYPE = port
