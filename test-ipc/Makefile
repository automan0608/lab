
CFLAGS := 
LDFLAGS := 

objs = main-01-fifo-write.o main-02-fifo-read.o

target = main-01-fifo-write.out main-02-fifo-read.out

all:
	$(MAKE) $(target)

$(target):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(target)
