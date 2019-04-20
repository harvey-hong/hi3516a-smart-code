include ./../user.param
include ./../config.param
include ./../Makefile.param

TARGET = libgetframe.so

INCLUDE += -I ./../include/common_def
INCLUDE += -I ./../include/common_api

$(TARGET):GetFrame.cpp
	$(CC) $(INCLUDE) -shared -fPIC GetFrame.cpp $(LDFLAGS) $(CFLAGS) -o $(TARGET) 
ifdef STRIP
	$(CROSS)strip $(TARGET)
endif

install:
	cp $(TARGET) $(COPY_NFS_DIR)
	cp $(TARGET) $(TARGET_COPY)
	
clean:
	@rm -rf $(TARGET)	
	
