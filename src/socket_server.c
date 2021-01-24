#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/mysock.uds"
#define BUFSIZE 1000

int main() {

  // create socket
  int socket_fd;
  if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // setup socket address
  struct sockaddr_un addr;
  memset(&addr, '\0', sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path));
  socklen_t socklen = sizeof(struct sockaddr_un);

  // bind socket
  unlink(SOCKET_PATH);
  int bind_res;
  if ((bind_res = bind(socket_fd, (struct sockaddr *)&addr, socklen)) != 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // start listening
  int listen_res;
  if ((listen_res = listen(socket_fd, 1)) != 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  char *buf = malloc(BUFSIZE * sizeof(char));

  // listen to connections forever
  while (1) {

    // accept connection
    int acc_res;
    if ((acc_res = accept(socket_fd, (struct sockaddr *)&addr, &socklen)) < 1) {
      perror("accept failed");
      continue;
    }

    while (1) {
        memset(buf, '\0', BUFSIZE);
      // read message
      int read_res;
      if ((read_res = read(acc_res, buf, BUFSIZE)) < 1) {
        if (read_res == 0) {
          fprintf(stderr, "EOF detected.\n");
        } else {
          printf("%d\n", read_res);
          perror("read failed");
        }
        break;
      }

      printf("%s", buf);
    }
  }

  free(buf);
}
