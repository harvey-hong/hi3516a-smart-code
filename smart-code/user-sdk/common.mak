#!/usr/bin/make -f

#enable this macro only when you want to build it singly

include ../user.param
include ../config.param
include ../Makefile.param

CFLAGS+= -DEGUI_FOR_ICAMERA_NXP8850_BASED_DVR 

CFLAGS+= -DEGUI_FOR_ICAMERA_${TYPE}_BASED_DVR -DSUPPORT_CRECORD -DSUPPORT_CODER -DSUPPORT_OSD -DSUPPORT_IPRESET -DSUPPORT_ALARMIN -DSUPPORT_ALARMOUT -DSUPPORT_CAPTURE -DSUPPORT_MOTION -DSUPPORT_TALKING -DSUPPORT_TIME -DSUPPORT_WATCHDOG -D$(PRODUCT_TYPE) -fvisibility=hidden

RM=rm -rf
INSTALL=install -cv -m 777

CFLAGS += -fPIC -shared -DSUPPORT_WIFI
CFLAGS += -DONVIF_SUPPORT
#CFLAGS += -DRTMP_SUPPORT
CFLAGS += -DUPNP_SUPPORT

CFLAGS+= -Wall
CFLAGS+= -D_POSIX_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -DMEMWATCH -DMW_STDIO -DSECRET_SUPPORT -D$(PRODUCT_LAYER)
CFLAGS+= -Wall -W -Wpointer-arith -Wbad-function-cast -Wcast-qual
RFLAGS+= $(CFLAGS) -O3 -DNDEBUG
DFLAGS+= $(CFLAGS) -W -g
TESTFLAGS+= -O3 -DNDEBUG -Wall
#LFLAGS+= -lpthread
LIBPATH+=  -L$(CROSS_COMPILE_PATH)/lib -L$(CROSS_COMPILE_PATH)/usr/lib
INCPATH+= -I.. -I../include -I../include/newhie -I../PUB -I../PAR -I../../modules/include -I$(CROSS_COMPILE_PATH)/usr/include 
INCPATH+= -I../include/common_api -I../include/common_def

LDFLAGS += -L$(TARGET_COPY)

MPATH=$(shell pwd)
LIBNAME=$(notdir $(MPATH))
TARGET = lib$(LIBNAME).so


OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS+= $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o:%.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) $(DFLAGS) $(INCLUDE) $(INCPATH) $(LIBPATH) -c $^ -o $@
	
%.o:%.c
	$(CC) $(LDFLAGS) $(CFLAGS) $(DFLAGS) $(INCLUDE) $(INCPATH) $(LIBPATH) -c $^ -o $@

$(TARGET):  $(OBJECTS)
	$(CC) $(INCLUDE) -o $@ -shared -fPIC $(CFLAGS) $(LDFLAGS) $^ $(LIBS)
	
ifdef STRIP
	$(CROSS)strip $(TARGET)
endif

ifdef COPY_NFS_DIR
	 cp $(TARGET) $(COPY_NFS_DIR)
endif		
	
install:
#	cp $(TARGET) $(TARGET_INSTALL)
	cp $(TARGET) $(TARGET_COPY)

clean:
	@ rm -f ${OBJECTS}
	@ rm -f $(TARGET)
