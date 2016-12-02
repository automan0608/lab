
CFLAGS :=  -lpthread
LDFLAGS := 

objs = main-01-fifo-write.o main-02-fifo-read.o

target = main-01-fifo-write.out main-02-fifo-read.out \
		 main-03-mmap-1process.out

all:
	$(MAKE) $(target)

$(target):%.out:%.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(target)
