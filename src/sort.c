#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char a[] = {'1', '2', '3', '\0'};
  char *elePt = a;

  while (*elePt != '\0') {
    printf("%c\n", *elePt);
    elePt++;
  }
}

int s2(int argc, char *argv[]) {
  char a[] = {'1', '2', '3', '\0'};
  char(*arrPt)[sizeof(a) / sizeof(char)] = &a;
  char *elePt = a;

  printf("%s\t%s\n", elePt, arrPt);
  printf("%c\t%s\n", *elePt, *arrPt);
  printf("%d", sizeof(*arrPt) / sizeof(*elePt));
  printf("\n");

  elePt++;

  printf("%s\t%s\n", elePt, arrPt);
  printf("%c\t%s\n", *elePt, *arrPt);
}
