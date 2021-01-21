#include <stdlib.h>
#include <stdio.h>

#define SIZE (10000)

int main() {
    char *test = malloc(10);
    test = "hello wor";
    printf("%p\n", test);

    char **ptr = &test;

    test++;
    printf("%p\n", test);

    test = *ptr;

    printf("%p\n", test);
}
