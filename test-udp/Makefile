
CFLAGS := 
LDFLAGS := 

objs = main-01-svr.o main-01-cli.o  \
       main-02-broadcast-recver.o \
       main-02-broadcast-sender.o 


target =  main-01-svr.out main-01-cli.out \
	  main-02-broadcast-recver.out  \
	  main-02-broadcast-sender.out

all:
	$(MAKE) $(target)

$(target):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(target)
