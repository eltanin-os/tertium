PREFIX=    /usr/local
MANPREFIX= $(PREFIX)/share/man

AR     = ar
CC     = cc
RANLIB = ranlib

CFLAGS   = -Os -std=c99 -Wall -pedantic
LDFLAGS  =

# OSes:
# port (system libc)
OSNAME  = port
# Arch:
# port (system libc)
OBJTYPE = port
