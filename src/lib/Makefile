include ../Config.mk

OBJS = lib.o

TARGET = libkzlib.a

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I. -I../driver
#CFLAGS += -g
CFLAGS += -Os

ARFLAGS = r

.SUFFIXES: .c .o

all : $(TARGET)

$(TARGET) :	$(OBJS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

.c.o : $<
	$(CC) -c $(CFLAGS) $<

clean :
	rm -f *.o $(TARGET)
