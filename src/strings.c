#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/time.h>
// #include <time.h>

#define ALPHA_MIN (65)
#define ALPHA_MAX (122)
#define STRING_COUNT (100)

void realloc_each_cat();
void to_hex_str(char *out, const char *str, const size_t);
void from_hex_str(char *out, const char *hex_str, const size_t str_size);

int main(int argc, char *argv[]) { realloc_each_cat(); }

void realloc_each_cat() {
  size_t str_size = 1;
  char *str = malloc(1 * sizeof(char));

  // Generate random seed from
  FILE *fp = fopen("/dev/random", "r");
  unsigned int seed;
  fread(&seed, sizeof(unsigned int), 1, fp);
  srand(seed);

  // Use a seed that changes more than once a second
  // struct timeval time;
  // gettimeofday(&time, NULL);
  // srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

  // Use a seed that changes every second
  // srand(time(NULL));
  for (size_t i = 0; i < STRING_COUNT; i++) {
    const size_t chr_size = (rand() % 100) + 1;
    char add_char[chr_size];
    for (size_t j = 0; j < chr_size - 1; j++) {
      add_char[j] = (rand() % (ALPHA_MAX + 1 - ALPHA_MIN)) + ALPHA_MIN;
    }
    add_char[chr_size - 1] = '\0';

    str_size += chr_size - 1;
    str = realloc(str, str_size);

    strcat(str, add_char);
  }

  printf("str len:\t%lu\n", strlen(str));
  printf("str size:\t%lu\n", str_size);

  char *hex_str = malloc(str_size * 2);
  to_hex_str(hex_str, str, str_size);

  char *parse = malloc(str_size);
  from_hex_str(parse, hex_str, str_size * 2);

  printf("%s\n\n", hex_str);

  free(hex_str);
  hex_str = NULL;

  printf("%s\n\n", str);
  printf("%s\n\n", parse);

  printf("fst: %c\tlst: %c\n", str[str_size - 2], str[0]);

  free(str);
  str = NULL;

  printf("fst: %c\tlst: %c\n", parse[str_size - 2], parse[0]);

  free(parse);
  parse = NULL;
}

void to_hex_str(char *out, const char *str, const size_t str_size) {
  for (size_t i = 0; i < str_size; i++) {
    char hex_buf[3];
    sprintf(hex_buf, "%02x", str[i]);
    strcat(out, hex_buf);
  }
}

void from_hex_str(char *out, const char *hex_str, const size_t str_size) {
  for (size_t i = 0; i < str_size; i = i + 2) {
    char *ptr = NULL;
    char chrs[] = {hex_str[i], hex_str[i + 1]};
    out[i / 2] = strtol(chrs, &ptr, 16);
  }
}
