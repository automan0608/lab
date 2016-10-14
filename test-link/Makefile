
#CC := gcc
CC := /home/zhaosheng/sdk-toolchain/toolchain-sohointl-vr600v2/usr/bin/mips-unknown-linux-uclibc-gcc

CFLAGS += -I./dir1/ -I./dir2/
LDFLAGS += -L./dir1/ -L./dir2/ 

#LDFLAGS +=  -lfun1 -ltest
LDFLAGS +=  -ltest -lfun1

all:
	$(CC) main.c $(CFLAGS) $(LDFLAGS)

clean:
	rm a.out
