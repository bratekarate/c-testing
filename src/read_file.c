#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nettle/hmac.h>

#define SIZE (4096)

int main(int argc, char *argv[]) {

  FILE *fp;

  if (argc < 2) {
    fp = stdin;
  } else {
    fp = fopen(argv[1], "r");
  }

  if (fp == NULL) {
    perror("Error");
    return 1;
  }

  char *str_ptr = malloc(SIZE);
  char buf[SIZE];
  while (fgets(buf, SIZE, fp)) {
    int new_size = strlen(str_ptr) + strlen(buf);

    str_ptr = realloc(str_ptr, new_size + 1);

    if (str_ptr == NULL) {
    }

    strcpy(str_ptr + strlen(str_ptr), buf);
  }

  printf("%s", str_ptr);
}
