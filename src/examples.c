#include <Python.h>
#include <inttypes.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bytes(char *bytes, int len);
void print_hex_bytes(char *bytes, int len);
void print_uint8(u_int8_t *bytes, int len);
const char *calc_aes_key(char *passphrase, int rounds, char *salt);

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
  char *rest = malloc(0);
  char buf;
  while (!feof(fp)) {
    rest = realloc(rest, i + 1);
    rest[i] = fgetc(fp);
    i++; // TODO: why is i after loop the size of rest bytes + 1?
  }
  i--;

  fclose(fp);

  char hmac_sha256[32];
  int j;
  for (j = 0; j < 32; j++) {
    hmac_sha256[32 - 1 - j] = rest[i - 1 - j];
  }

  int rest_size = i;
  i -= j;

  const char *aes_key = calc_aes_key(argv[2], rounds, salt);

  printf("%s\n", aes_key);
}

// Extract AES-256-CTR key with embedded python
const char *calc_aes_key(char *passphrase, int rounds, char *salt) {
  Py_Initialize();
  PyObject *moduleMainString = PyUnicode_FromString("__main__");
  PyObject *moduleMain = PyImport_Import(moduleMainString);

  PyRun_SimpleString("import sys\nimport pbkdf2\n"
                     "from Crypto.Hash import SHA512\n"
                     "from Crypto.Hash import HMAC\n\n"
                     "def calc_key(passphrase, iterations, salt):\n"
                     "    key = pbkdf2.PBKDF2(passphrase, salt, iterations, "
                     "SHA512, HMAC).hexread(64)\n"
                     "    return key\n");

  PyObject *func = PyObject_GetAttrString(moduleMain, "calc_key");
  PyObject *args =
      PyTuple_Pack(3, PyUnicode_FromString(passphrase), PyLong_FromLong(rounds),
                   PyBytes_FromString(salt));

  PyObject *result = PyObject_CallObject(func, args);
  Py_Finalize();

  return PyUnicode_AsUTF8(result);
}

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

