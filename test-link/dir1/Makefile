
target = libfun1.so

all:
	gcc -shared -fPIC -o $(target) fun1.c

install:
	sudo cp $(target) /usr/local/lib/

clean:
	rm $(target)
