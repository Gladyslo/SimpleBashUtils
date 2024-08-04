#include "cat_function.h"

int main(int argc, char **argv) {
  cat_flags flags = {false};
  if (flag_parser(argc, argv, &flags)) read_file(argc, argv, flags);
  return 0;
}
int flag_parser(int argc, char **argv, struct cat_flags *flags) {
  int opt;
  int flag = 1;  // check that flags and filenames are correct
  const char *short_flags = SHORT_FLAGS;
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, short_flags, long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flags->b = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'T':
        flags->T = true;
        break;
      case 't':
        flags->T = true;
        flags->v = true;
        break;
      case 'E':
        flags->E = true;
        break;
      case 'e':
        flags->E = true;
        flags->v = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case '?':
        flag = 0;
        break;
      default:
        printf("incorrect flag");
        break;
    }
  }
  return flag;
}

void read_file(int argc, char **argv, struct cat_flags flags) {
  // check multiple files
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
    } else {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
        perror(argv[i]);
      } else {
        print_file(fp, &flags);
      }
      fclose(fp);
    }
  }
}

void print_file(FILE *fp, struct cat_flags *flags) {
  int current_char;
  int previous_char = CHECK_1st_LINE;
  int count = COUNTER_LINES;
  int unused_counter = 1;
  while ((current_char = fgetc(fp)) != EOF) {
    if (flags->s == true)
      s_flag(flags, fp, &current_char, &previous_char, &count, unused_counter);
    if (flags->n == true && flags->b == false &&
        (previous_char == '\n' || unused_counter == 1)) {
      printf("%6d\t", count++);
    }
    if (flags->b == true && current_char != '\n' &&
        (previous_char == '\n' || unused_counter == 1)) {
      printf("%6d\t", count++);
    }
    if (flags->T == true && current_char == '\t') {
      printf("^I");
      while ((current_char = fgetc(fp)) == '\t') printf("^I");
    }
    if ((flags->v == true)) v_flag(&current_char);
    if (flags->E == true) {
      e_flag(flags, &current_char, &previous_char, unused_counter);
    }
    previous_char = current_char;
    fputc(current_char, stdout);
    unused_counter++;
  }
}

void s_flag(struct cat_flags *flags, FILE *fp, int *current_char,
            int *previous_char, int *count, int unused_counter) {
  if (*current_char == '\n' &&
      (*previous_char == '\n' || unused_counter == 1)) {
    while ((*current_char = fgetc(fp)) == '\n') *previous_char = *current_char;
    if (flags->E == true) {
      if (flags->b == true) printf("      \t$");
      if (flags->n == false && flags->b == false) printf("$");
      if (flags->n == true && flags->b == false) printf("%6d\t$", (*count)++);
    }
    if (flags->E == false && flags->n == true && flags->b == false)
      printf("%6d\t", (*count)++);
    printf("\n");
  }
}

void v_flag(int *symbol) {
  if (*symbol >= 0 && *symbol <= 31 && *symbol != '\n' && *symbol != '\t')
    printf("^");
  if (*symbol == 127) printf("^");
  if (*symbol > 127 && *symbol < 160) printf("M-^");
  if ((*symbol < 32 || (*symbol > 126 && *symbol < 160)) && *symbol != '\n' &&
      *symbol != '\t')
    *symbol = *symbol > 126 ? *symbol - 128 + 64 : *symbol + 64;
}

void e_flag(struct cat_flags *flags, int *current_char, int *previous_char,
            int unused_counter) {
  if (flags->b == true && *current_char == '\n' &&
      (*previous_char != '\n' && unused_counter != 1)) {
    printf("$");
  }
  if (flags->b == true && flags->s == false && *current_char == '\n' &&
      (*previous_char == '\n' || unused_counter == 1)) {
    printf("      \t$");
  }
  if (flags->b == false && *current_char == '\n' &&
      (*previous_char != '\n' || *previous_char == '\n')) {
    printf("$");
  }
}