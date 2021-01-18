#include <inttypes.h>
#include <nettle/hmac.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bytes(char *bytes, int len) {
  for (int i = 0; i < len; i++) {
    printf("%c", bytes[i]);
  }
}

void print_hex_bytes(char *bytes, int len) {
  for (int i = 0; i < len; i++) {
    printf("%02X", bytes[i]);
  }
}

void print_uint8(u_int8_t *bytes, int len) {
  for (int i = 0; i < len; i++) {
    printf("%" PRIu8, bytes[i]);
  }
}

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

  char format = fgetc(fp);

  int i;
  char salt[16];
  for (i = 0; i < 16; i++) {
    salt[i] = fgetc(fp);
  }

  char vec[16];
  for (i = 0; i < 16; i++) {
    vec[i] = fgetc(fp);
  }

  u_int8_t rnd_arr[4];
  for (i = 0; i < 4; i++) {
    rnd_arr[i] = fgetc(fp);
  }

  uint32_t rounds =
      (rnd_arr[0] << 24) + (rnd_arr[1] << 16) + (rnd_arr[2] << 8) + rnd_arr[3];

  i = 0;
  char *rest;
  char buf;
  while (!feof(fp)) {
    rest = realloc(rest, i + 1);
    rest[i] = fgetc(fp);
    i++; // TODO: why is i after loop the size of rest bytes + 1?
  }

  i--;

  char hmac_sha256[32];
  int j;
  for (j = 0; j < 32; j++) {
    hmac_sha256[32 - 1 - j] = rest[i - 1 - j];
  }

  int rest_size = i;
  i -= j;

  /*printf("%c", format);*/

  /*print_bytes(salt, 16);*/
  /*printf("\n");*/
  /*print_hex_bytes(salt, 16);*/

  /*print_bytes(vec, 16);*/

  /*print_bytes(rnd_arr, 4);*/

  /*printf("%d", rounds);*/

  /*print_bytes(rest, rest_size - 32);*/

  /*print_bytes(hmac_sha256, 32);*/

  /*printf("%d\n",*/
         /*i + 1 + 16 + 16 + 4 + 32); // should match byte size of input file*/
}
