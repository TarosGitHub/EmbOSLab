include ../Config.mk

OBJS = serial.o

TARGET = libkzdriver.a

CFLAGS += -I. -I../lib

.SUFFIXES: .c .o

all : $(TARGET)

debug :
	make all "BUILD_MODE = -g"

$(TARGET) :	$(OBJS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

.c.o : $<
	$(CC) -c $(CFLAGS) $<

clean :
	rm -f *.o $(TARGET)
