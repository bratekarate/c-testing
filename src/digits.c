#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digits(int n);

int main() {
  char *str = "Hello, World %d!";
  int no = 123;
  size_t l = strlen(str) - 2 + digits(no) +  1;
  char *out = malloc(l * sizeof(char));
  snprintf(out, l, str, no);
  fprintf(stderr, "Some error.\n");
  fprintf(stdout, "%s\n", out);
}

int digits(int n) {
  int c = 0;
  while (n > 0) {
    n/=10;
    c++;
  }
  return c;
}
