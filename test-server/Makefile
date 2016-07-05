
CFLAGS :=
LDFLAGS :=

objs = main-01-echo-serv.o main-01-echo-cli.o

target = main-01-echo-serv.out main-01-echo-cli.out

all:
	$(MAKE) $(target)

$(target):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(target)
