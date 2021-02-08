#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE (400)

char *read_malloc(const size_t bufsize, size_t *ret_size) {
  size_t size = bufsize;
  size_t used = 0;

  char *sp = malloc(bufsize * sizeof(char));
  char buf[bufsize];

  while (fgets(buf, bufsize, stdin) && buf[strlen(buf) - 1] != '\n') {
    if (used + bufsize > size) {
      size += bufsize + size * 1.6180;
      sp = realloc(sp, size);
    }
    char fmted[bufsize];
    sscanf(buf, "%[^\n]", fmted);
    strncat(sp, fmted, bufsize);
    used += bufsize;
  }

  return sp;
}

int main() {
    size_t size;
    char *str = read_malloc(BUFSIZE, &size);
    printf("%s\n", str);
    free(str);
}
