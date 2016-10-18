
CC 	:= gcc
CFLAGS 	+= -llua5.2
LDFLAGS += 

objs := main-01.o 			\
	main-02-dofile.o 		\
	main-03-load-cfg-simple.o	\
	main-04-load-cfg-table.o

targets := main-01.out			\
	   main-02-dofile.out		\
	   main-03-load-cfg-simple.out	\
	   main-04-load-cfg-table.out

all:$(targets)

$(targets):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) 

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) 

clean:
	-rm $(targets) *.o
