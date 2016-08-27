CFLAGS += -I./dir1/ -I./dir2/
LDFLAGS += -L./dir1/ -L./dir2/ 

#LDFLAGS +=  -lfun1 -ltest
LDFLAGS +=  -ltest -lfun1

all:
	gcc main.c $(CFLAGS) $(LDFLAGS)

clean:
	rm a.out
