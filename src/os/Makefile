include ../Config.mk

OBJS = startup.o main.o interrupt.o

TARGET = kozos

CFLAGS += -I. -I../lib -I../driver
CFLAGS += -DKOZOS

LFLAGS += -T ld.scr -L. -L../lib -lkzlib -L../driver -lkzdriver

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all : $(TARGET)

debug :
	make all "BUILD_MODE = -g"

$(TARGET) :	$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
	cp $(TARGET) $(TARGET).elf
	$(STRIP) $(TARGET)

.c.o : $<
	$(CC) -c $(CFLAGS) $<

.s.o : $<
	$(CC) -c $(CFLAGS) $<

clean :
	rm -f *.o $(TARGET)*
