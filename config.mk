PREFIX=    /usr/local
MANPREFIX= $(PREFIX)/share/man

AR     = ar
CC     = ecc
RANLIB = ranlib

CFLAGS   = -Os -std=c99 -Wall -pedantic
LDFLAGS  =

# OSes:
# port (system libc)
# linux
OSNAME  = port
# Arch:
# port (system libc)
# x86_64
OBJTYPE = port
