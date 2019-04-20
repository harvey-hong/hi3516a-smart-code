#CC=arm-hisiv100nptl-linux-g++
#STRIP=arm-hisiv100nptl-linux-strip
CC=g++
STRIP=strip

cflags= -c -I ./

test :
	$(CC) test.cpp -o test -L ../ -ldecoder265


clean :
	@ rm -f test 
