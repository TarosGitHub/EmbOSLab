PREFIX  = /usr/local
ARCH    = h8300-elf
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

H8WRITE = ../../tools/h8write/h8write.exe

# FreeBSD-4.x:/dev/cuaaX, FreeBSD-6.x:/dev/cuadX, FreeBSD(USB):/dev/cuaUx
# Linux:/dev/ttySx, Linux(USB):/dev/ttyUSBx, Windows:comX
H8WRITE_SERDEV = com3

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
#CFLAGS += -g
CFLAGS += -Os

LFLAGS = -static

ARFLAGS = r

export PREFIX
export ARCH
export BINDIR
export ADDNAME
export AR
export AS
export CC
export LD
export NM
export OBJCOPY
export OBJDUMP
export RANLIB
export STRIP
export H8WRITE
export H8WRITE_SERDEV
export CFLAGS
export LFLAGS
export ARFLAGS
