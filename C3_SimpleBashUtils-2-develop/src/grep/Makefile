CC=gcc
CFLAGS= -std=c11 -Werror -Wall -Wextra
LD_FLAGS= -o
BUILD_FILE= s21_grep.c


all: s21_grep

s21_grep: $(BUILD_FILE)
	$(CC) $(CFLAGS) $(BUILD_FILE) $(LD_FLAGS) s21_grep

clean: 
	rm -rf *.o
	rm -rf *.o
	rm -rf s21_grep

rebuild : clean all