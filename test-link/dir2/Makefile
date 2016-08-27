
objs = fun1.o fun2.o

all:$(objs)
	ar rcs libtest.a $(objs) 

$(objs):%.o:%.c
	gcc -o $@ -c $< 

clean:
	rm *.a $(objs)
