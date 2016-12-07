
CFLAGS  :=
LDFLAGS := -levent

src  := $(shell find -name *.c)
objs  := $(patsubst %.c, %.o, $(src))

target  := get_mjpeg.out

all:$(target)
	make $(target)

$(target):$(objs)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	-rm $(objs) $(target)

.PHONY:
	all, clean
