#include <nettle/hmac.h>
#include <olm/olm.h>
#include <python3.9/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (4096)

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

  char *str_ptr = malloc(SIZE);
  char buf[SIZE];
  while (fgets(buf, SIZE, fp)) {
    int new_size = strlen(str_ptr) + strlen(buf);

    str_ptr = realloc(str_ptr, new_size + 1);

    if (str_ptr == NULL) {
    }

    strcpy(str_ptr + strlen(str_ptr), buf);
  }

  /*printf("%s", str_ptr);*/
  /*printf("%lu\n", strlen(str_ptr));*/

  /*size_t size = olm_inbound_group_session_size();*/
  /*struct OlmInboundGroupSession *session = olm_inbound_group_session(&size);*/

  /*olm_unpickle_inbound_group_session(session, "tests", 4, str_ptr,*/
                                     /*strlen(str_ptr));*/

  /*printf("%s\n", olm_inbound_group_session_last_error(session));*/

  char *pargv[3];
  pargv[0] = "progname";
  pargv[1] = argv[2]; // passphrase
  pargv[2] = argv[3]; // iterations

  wchar_t **wpargv = PyMem_Malloc(sizeof(wchar_t *) * 3);
  for (int i = 0; i < 3; i++) {
    wchar_t *arg = Py_DecodeLocale(pargv[i], NULL);
    wpargv[i] = arg;
  }

  Py_SetProgramName(wpargv[0]);
  Py_Initialize();

  PySys_SetArgv(3, wpargv);
  /*fp = _Py_fopen(filename, "r");*/
  /*PyRun_SimpleFile(fp, filename);*/

  PyRun_SimpleString("import sys\nimport pbkdf2\nfrom Crypto.Hash import SHA512\nfrom Crypto.Hash import HMAC\n\npassphrase = sys.argv[1]\niterations = sys.argv[2]\nsalt = b''\nwith open('/tmp/salt', 'rb') as f:\n    byte = f.read(1)\n    salt += byte\n    while byte != b'':\n        byte = f.read(1)\n        salt += byte\nkey = pbkdf2.PBKDF2(passphrase, salt, int(iterations), SHA512, HMAC).hexread(64)\nprint(key)\n");

  Py_Finalize();

  return 0;
}
