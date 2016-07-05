
CFLAGS :=
LDFLAGS :=

objs = main-01.o main-02.o main-03-serv.o main-03-cli-signal.o \
	   main-03-cli-sigaction.o

target = main-01.out main-02.out main-03-serv.out main-03-cli-signal.out \
		 main-03-cli-sigaction.out

all:
	$(MAKE) $(target)

$(target):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(target)
