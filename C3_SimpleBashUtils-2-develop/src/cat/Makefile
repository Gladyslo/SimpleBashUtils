CC=gcc
CFLAGS= -std=c11 -Werror -Wall -Wextra
LD_FLAGS= -o
BUILD_FILE= cat_function.c


all: s21_cat

s21_cat: $(BUILD_FILE)
	$(CC) $(CFLAGS) $(BUILD_FILE) $(LD_FLAGS) s21_cat

clean: 
	rm -rf *.o
	rm -rf *.o
	rm -rf s21_cat

rebuild : clean all