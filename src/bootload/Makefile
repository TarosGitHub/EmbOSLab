include ../Config.mk

OBJS = vector.o startup.o intr.o main.o xmodem.o elf.o interrupt.o

TARGET = kzload

CFLAGS += -I. -I../lib -I../driver
CFLAGS += -DKZLOAD

LFLAGS += -T ld.scr -L. -L../lib -lkzlib -L../driver -lkzdriver

.SUFFIXES: .c .o
.SUFFIXES: .s .o
.SUFFIXES: .S .o

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

.S.o : $<
	$(CC) -c $(CFLAGS) $<

$(TARGET).mot :	$(TARGET)
	$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot

image : $(TARGET).mot

write : $(TARGET).mot
	$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

clean :
	rm -f *.o $(TARGET)*
