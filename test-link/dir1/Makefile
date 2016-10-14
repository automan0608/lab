
#CC := gcc
CC := /home/zhaosheng/sdk-toolchain/toolchain-sohointl-vr600v2/usr/bin/mips-unknown-linux-uclibc-gcc
target = libfun1.so

all:
	$(CC) -shared -fPIC -o $(target) fun1.c

install:
	sudo cp $(target) /usr/local/lib/

clean:
	rm $(target)
