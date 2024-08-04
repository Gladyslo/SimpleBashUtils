#ifndef CAT_FUNCTION_H
#define CAT_FUNCTION_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SHORT_FLAGS "+bnstTeEv"
#define COUNTER_LINES 1
#define CHECK_1st_LINE ' '

typedef struct cat_flags {
  int b, n, s, t, T, e, E, v;
} cat_flags;

void read_file(int argc, char **argv, struct cat_flags flags);
int flag_parser(int argc, char **argv, struct cat_flags *flags);
void print_file(FILE *fp, struct cat_flags *flags);
void v_flag(int *symbol);
void s_flag(struct cat_flags *flags, FILE *fp, int *current_char,
            int *previous_char, int *count, int unused_counter);
void e_flag(struct cat_flags *flags, int *current_char, int *previous_char,
            int unused_counter);

#endif