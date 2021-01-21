#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 6;
    int *p = &i;
    int **pp = &p;

    pp++;
   
    int j = 9;
    int *pj = &j;
    pp = &pj;

    printf("%p\n", p);
    printf("%p\n", pp);

    printf("%d\n", *p);
    printf("%d\n", **pp);
    pp--;
    printf("%d\n", **pp);
}
