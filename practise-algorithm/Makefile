
CFLAGS  :=
LDFLAGS :=

src  := $(shell find -name "*c")
objs  := $(patsubst %.c, %.o, $(src))

target  := $(patsubst %.c, %.out, $(src))

all:
#	echo $(src)
	echo $(target)
#	echo $(objs)
	make $(target)

$(target):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	-rm $(objs) $(target)

.PHONY:
	all, clean
