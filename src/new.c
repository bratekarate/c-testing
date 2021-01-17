#include <stdio.h>
#include <stdlib.h>

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define NELEMS_STR(x) (sizeof(x) / sizeof((x)[0]) - 1)

struct Array {
  int *arr;
  int length;
  int count;
};

// Iterate char array by index.
// Length must be provided as the array will be transformed to a pointer. Size
// information is lost
void iterate_index_chr(char *b, int len) {
  for (int i = 0; i < len; i++) {
    printf("%c\n", b[i]);
  }
}

// Iterate char array using pointer.
void iterate_pointer_chr(char *b, int len) {
  for (char *p = b; p < b + len; p++) {
    printf("%c\n", *p);
  }
}

// Iterate custom array struct using pointer.
void iterate_struct_pointer(struct Array *arr) {
  for (int *p = arr->arr; p < arr->arr + arr->length; p++) {
    printf("%d\n", *p);
  }
}

// Iterate int array using index
void iterate_index_int(int i[], int len) {
    for (int j = 0; j < len; j++) {
        printf("%d\n", i[j]);
    }
}

int main() {
  // # Strings
  // Declare a string as char array by initializing a char array
  char str0[] = {'h', 'a', 'h', 'a', '\0'};
  printf("%s\n", str0);

  // Declare a string as char pointer by initializing a char array
  char str1_arr[] = {'h', 'a', 'h', 'a', '\0'};
  char *str1 = str1_arr;
  printf("%s\n", str1);

  // ... or inline (array will be anonmyous; only pointer is available)
  char *str2 = (char[]){'h', 'a', 'h', 'a', '\0'};
  printf("%s\n", str2);

  // Declare a string inline
  char str3[] = "haha";
  printf("%s\n", str3);

  // Declare a string as pointer
  char *str4 = "haha";
  printf("%s\n", str4);

  // Iterate char array using pointers.
  // strlen from <string.h> could also be used to get the length
  iterate_pointer_chr(str0, NELEMS_STR(str0));
  iterate_index_chr(str0, NELEMS_STR(str0));

  // # Int arrays
  int i[] = { 1,2,3,4,5};
  int i_len = NELEMS(i);

  // Iterate int array using sizeof
  for (int j = 0; j < NELEMS(i); j++) {
      printf("%d\n", i[j]);
  }
  // Iterate int array in a function. Length must be provided in this case
  iterate_index_int(i, i_len);

  // Use a custom struct to aggregate length and count information with the
  // array, avoiding to pass around multiple variables for a single array.
  int nums[] = {2, 4, 5, 6};
  int C_LEN = NELEMS(nums);

  struct Array arr = {.arr = nums, .length = NELEMS(nums), .count = NELEMS(nums)};

  // struct is not transformed into a pointer automatically, use &
  iterate_struct_pointer(&arr);

  return 0;
}
