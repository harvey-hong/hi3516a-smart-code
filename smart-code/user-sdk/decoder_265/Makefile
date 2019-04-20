include ./../user.param
include ./../config.param
include ./../Makefile.param


INCLUDE += -I ./
INCLUDE += -I ./../include/common_api

cflags += -fPIC  -shared -D_LINUX -DLINUX -D_HISI_ARM
cflags += -fvisibility=hidden

BIN = libdecoder265.so

.PHONY:all
all: $(BIN)

install:
	cp $(BIN) $(TARGET_COPY)

$(BIN) : bitstream.o de265.o nal.o scan.o refpic.o vui.o vps.o sps.o h265_decoder.o
	$(CC) -fPIC -shared -o $(BIN) bitstream.o scan.o de265.o nal.o  refpic.o  vui.o vps.o sps.o  h265_decoder.o
ifdef STRIP
	$(CROSS)strip $(BIN)
endif

%.o : %.cpp
	$(CC) -c $(cflags) $(INCLUDE)  -o $@ $<

clean :
	rm -f *.o
	rm -f $(BIN)
