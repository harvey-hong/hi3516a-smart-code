include ./../../../user.param
include ./../../../config.param
include ./../../../Makefile.param

INCLUDE += -I ./../../../include/common_def
INCLUDE += -I ./../../../include/common_api

SRC_C = $(wildcard *.c)
SRC_CPP = $(wildcard *.cpp)
BIN  = ../../bin/linux/arm/librtsp.so
CXXFLAGS = $(CFLAGS) -D_LINUX -DLINUX -D_HISI_ARM -fvisibility=hidden
RM = rm -f
TGT = $(SRC_C:.c=.o) $(SRC_CPP:.cpp=.o)
VPATH = ./\
	./-B\
	./-F
vpath %.o ../../bin/linux/arm/temp

.PHONY: all all-before all-after clean clean-custom

all: $(BIN)

clean: clean-custom
	${RM} ../../bin/linux/arm/temp/*.o $(BIN)

install:
	cp $(BIN) $(TARGET_COPY)
	cp $(BIN) $(COPY_NFS_DIR)

$(BIN): $(TGT)
	$(CC) $(CXXFLAGS) $(INCLUDE) -Wall -fPIC -s -shared -O2 ../../bin/linux/arm/temp/*.o -o $(BIN)
ifdef STRIP
	$(CROSS)strip $(BIN)
endif
	
%.o:%.c
	$(CC) -c $? -s -O2 $(INCLUDE) -fPIC -o ../../bin/linux/arm/temp/$@ $(CXXFLAGS)
%.o:%.cpp
	$(CC) -c $? -s -O2 $(INCLUDE) -fPIC -o ../../bin/linux/arm/temp/$@ $(CXXFLAGS)
