#include <stdint.h>
#include <stdio.h>

/* NOLINTBEGIN(readability-magic-numbers) */
int main() {
  const int mask = 0x000000ff;

  const unsigned char x = 234;
  uint32_t arr[2] = { 0x0, 0x0 };
  
  const uint8_t a = 230;
  const uint8_t b = 23;
  const uint8_t c = 2;
  const uint8_t d = 100;
  const uint8_t e = 230;
  const uint8_t f = 23;
  const uint8_t g = 2;
  const uint8_t h = 100;

  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[0] = (arr[0] | a << 24);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[0] = (arr[0] | b << 16);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[0] = (arr[0] | c << 8);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[0] = (arr[0] | d);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[1] = (arr[1] | e << 24);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[1] = (arr[1] | f << 16);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[1] = (arr[1] | g << 8);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  arr[1] = (arr[1] | h);
  printf("arr: %032b%032b\n", arr[0], arr[1]);
  printf("a  : %d\n", (arr[0] >> 24 & mask));
  printf("b  : %d\n", (arr[0] >> 16 & mask));
  printf("c  : %d\n", (arr[0] >> 8 & mask));
  printf("d  : %d\n", (arr[0] & mask));
  printf("e  : %d\n", (arr[1] >> 24 & mask));
  printf("f  : %d\n", (arr[1] >> 16 & mask));
  printf("g  : %d\n", (arr[1] >> 8 & mask));
  printf("h  : %d\n", (arr[1] & mask));
}
/* NOLINTEND(readability-magic-numbers) */
