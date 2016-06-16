
CC := gcc
AR := ar

LIB_NAME = libmain.a
LIB_FILE = main.o p1.o

TARGET = a.out
TARGET_FILE = p2.o

all:$(LIB_FILE) $(TARGET_FILE)
	$(AR) rcs $(LIB_NAME) $(LIB_FILE)
	$(CC) -o $(TARGET) $(TARGET_FILE) -lmain -L./

$(LIB_FILE):%.o:%.c
	$(CC) -o $@ -c $<

$(TARGET_FILE):%.o:%.c
	$(CC) -o $@ -c $<

clean:
	-rm -rf *.o *.out $(LIB_NAME) $(TARGET)
