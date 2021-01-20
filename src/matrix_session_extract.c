#include <Python.h>
#include <inttypes.h>
#include <locale.h>
#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALT_LEN (16)
#define VECTOR_LEN (16)
#define ROUNDS_LEN (4)
#define HMAC_SHA256_LEN (32)
#define AES_KEY_LEN (64)

void print_bytes(const char *bytes, const size_t len);
void print_hex_bytes(const char *bytes, const size_t len);
void print_uint8(const u_int8_t *bytes, const size_t len);
const unsigned char *calc_aes_key(const char *passphrase, const size_t rounds,
                                  const char *salt);

int main(int argc, char *argv[]) {

  FILE *fp;

  switch (argc) {
  case 3:
    fp = stdin;
    break;
  case 4:
    fp = fopen(argv[3], "r");
    break;
  default:
    fprintf(stderr,
            "Error: Need at least a passphrase and an output filepath.\n");
    exit(1);
    break;
  }

  if (fp == NULL) {
    perror("Error");
    return 1;
  }

  const char format = fgetc(fp);

  size_t i;
  char salt[SALT_LEN + 1];
  for (i = 0; i < SALT_LEN; i++) {
    salt[i] = fgetc(fp);
  }
  salt[i] = '\0'; // \0 character necessary for python object conversion

  char vec[VECTOR_LEN];
  for (i = 0; i < VECTOR_LEN; i++) {
    vec[i] = fgetc(fp);
  }

  u_int8_t rnd_arr[ROUNDS_LEN];
  for (i = 0; i < ROUNDS_LEN; i++) {
    rnd_arr[i] = fgetc(fp);
  }

  i = 0;
  char *rest = malloc(0);
  char buf;
  while (!feof(fp)) {
    rest = realloc(rest, i + 1);
    rest[i] = fgetc(fp);
    i++; // TODO: why is i after loop the size of rest bytes + 1?
  }

  fclose(fp);

  if (i < HMAC_SHA256_LEN + 1) {
    fprintf(stderr, "Error: File content is too short.");
    exit(1);
  }

  i--; // see TODO above

  char hmac_sha256[HMAC_SHA256_LEN];
  size_t j;
  for (j = 0; j < HMAC_SHA256_LEN; j++) {
    hmac_sha256[HMAC_SHA256_LEN - 1 - j] = rest[i - 1 - j];
  }

  i -= j;

  fp = fopen(argv[1], "w");
  for (size_t k = 0; k < i; k++) {
    fputc(rest[k], fp);
  }

  fclose(fp);

  const uint32_t rounds =
      (rnd_arr[0] << 24) + (rnd_arr[1] << 16) + (rnd_arr[2] << 8) + rnd_arr[3];

  const unsigned char *aes_key = calc_aes_key(argv[2], rounds, salt);

  // print resulting key and initialization vector
  for (size_t c = 0; c < AES_KEY_LEN; c++) {
    printf("%02x", aes_key[c]);
  }
  printf(" ");
  for (size_t c = 0; c < VECTOR_LEN; c++) {
    printf("%02x", (const unsigned char)(vec[c]));
  }
  printf("\n");

  /*struct aes_key_st *AES_key =*/
  /*(struct aes_key_st *)malloc(sizeof(struct aes_key_st));*/

  /*if (AES_set_decrypt_key((const unsigned char *)("key"), 256, AES_key) < 0)
   * {*/
  /*fprintf(stderr, "Could not set encryption key.");*/
  /*exit(1);*/
  /*}*/

  /*unsigned char out[100000];*/
  /*const char in[i];*/
  /*AES_decrypt((const unsigned char *)(rest), out, AES_key);*/
  /*printf("%lu\n", strlen(out));*/
}

// Extract AES-256-CTR key with embedded python
const unsigned char *calc_aes_key(const char *passphrase, const size_t rounds,
                                  const char *salt) {
  Py_Initialize();
  PyObject *moduleMainString = PyUnicode_FromString("__main__");
  PyObject *moduleMain = PyImport_Import(moduleMainString);

  PyRun_SimpleString("import sys\nimport pbkdf2\n"
                     "from Crypto.Hash import SHA512\n"
                     "from Crypto.Hash import HMAC\n\n"
                     "def calc_key(passphrase, iterations, salt):\n"
                     "    key = pbkdf2.PBKDF2(passphrase, salt, iterations, "
                     "SHA512, HMAC).read(64)\n"
                     "    return key\n");

  PyObject *func = PyObject_GetAttrString(moduleMain, "calc_key");
  PyObject *args =
      PyTuple_Pack(3, PyUnicode_FromString(passphrase), PyLong_FromLong(rounds),
                   PyBytes_FromString(salt));

  PyObject *result = PyObject_CallObject(func, args);
  Py_Finalize();

  /*return (const unsigned char *)PyUnicode_AsUTF8(result);*/
  return (const unsigned char *)PyBytes_AsString(result);
}

void print_bytes(const char *bytes, const size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%c", bytes[i]);
  }
}

void print_hex_bytes(const char *bytes, const size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%02X", bytes[i]);
  }
}

void print_uint8(const u_int8_t *bytes, const size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%" PRIu8, bytes[i]);
  }
}
