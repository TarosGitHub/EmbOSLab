include ../Config.mk

OBJS = serial.o

TARGET = libkzdriver.a

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I. -I../lib
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
