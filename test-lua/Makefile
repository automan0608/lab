
CC 	:= gcc
CFLAGS 	+= -llua5.2
LDFLAGS +=  -g

LIBFLAGS += -shared -fPIC

objs := main-01.o 			\
	main-02-dofile.o 		\
	main-03-load-cfg-simple.o	\
	main-04-load-cfg-table.o	\
	main-05-load-cfg-colorname.o	\
	main-06-call-func.o		\

targets := main-01.out				\
	   main-02-dofile.out			\
	   main-03-load-cfg-simple.out		\
	   main-04-load-cfg-table.out		\
	   main-05-load-cfg-colorname.out 	\
	   main-06-call-func.out 		\

libs := array_lib.so counter_lib.so

all:$(targets) $(libs)

$(targets):%.out:%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) 

$(objs):%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) 

array_lib.so:main-08-userdata.c
	$(CC) $(LIBFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< 

counter_lib.so:main-07-upvalue.c
	$(CC) $(LIBFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< 

clean:
	-rm $(targets) $(libs) *.o
