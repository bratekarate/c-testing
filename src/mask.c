#include <stdio.h>

int main() {
  int mask = 0x000000ff;

  unsigned char x = 234;
  int arr = 0x0;
  
  unsigned char a = 230;
  char b = 23;
  char c = 2;
  char d = 100;

  printf("arr: %032b\n",arr);
  arr = (arr | a << 24);
  printf("arr: %032b\n", arr);
  arr = (arr | b << 16);
  printf("arr: %032b\n", arr);
  arr = (arr | c << 8);
  printf("arr: %032b\n", arr);
  arr = (arr | d);
  printf("arr: %032b\n", arr);
  printf("a  : %d\n", (arr >> 24 & mask));
  printf("b  : %d\n", (arr >> 16 & mask));
  printf("c  : %d\n", (arr >> 8 & mask));
  printf("d  : %d\n", (arr & mask));
}
