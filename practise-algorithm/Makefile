
CFLAGS  :=
LDFLAGS :=

src  := $(shell find -name *.c)
objs  := $(patsubst %.c, %.o, $(src))

target  := $(patsubst %.c, %.out, $(src))

all:
#	echo $(target)
#	echo $(objs)
	make $(target)

$(target):$(objs)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	-rm $(objs) $(target)

.PHONY:
	all, clean
