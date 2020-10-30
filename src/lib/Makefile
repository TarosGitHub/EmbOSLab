include ../Config.mk

OBJS = lib.o

TARGET = libkzlib.a

CFLAGS += -I. -I../driver

.SUFFIXES: .c .o

all : $(TARGET)

$(TARGET) :	$(OBJS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

.c.o : $<
	$(CC) -c $(CFLAGS) $<

clean :
	rm -f *.o $(TARGET)
