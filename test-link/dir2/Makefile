
#CC := gcc
#AR := ar
CC := /home/zhaosheng/sdk-toolchain/toolchain-sohointl-vr600v2/usr/bin/mips-unknown-linux-uclibc-gcc
AR := /home/zhaosheng/sdk-toolchain/toolchain-sohointl-vr600v2/usr/bin/mips-unknown-linux-uclibc-ar

objs = fun1.o fun2.o

all:$(objs)
	$(AR) rcs libtest.a $(objs) 

$(objs):%.o:%.c
	$(CC) -o $@ -c $< 

clean:
	rm *.a $(objs)
