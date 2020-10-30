include Config.mk

TARGET = bootload os
TARGET_REQ = lib driver

.PHONY: all $(TARGET_REQ) $(TARGET)

all : $(TARGET)

debug :
	make all "BUILD_MODE = -g"

$(TARGET) : $(TARGET_REQ)
	make --directory=$@

$(TARGET_REQ) :
	make --directory=$@

clean :
	for d in $(TARGET) $(TARGET_REQ); \
	do \
		make --directory=$$d clean; \
	done

# Rules for bootload
image : bootload
	make --directory=bootload image

write :
	make --directory=bootload write
