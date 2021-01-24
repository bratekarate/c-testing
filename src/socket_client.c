#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKPATH "/tmp/mysock.uds"
#define BUFSIZE (5000)

int main() {

  int socket_fd;

  if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un addr;
  memset(&addr, '\0', sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKPATH, sizeof(addr.sun_path));
  socklen_t len = sizeof(struct sockaddr_un);

  int conn_res;
  if ((conn_res = connect(socket_fd, (struct sockaddr *)&addr, len)) != 0) {
    perror("connect failed");
    exit(EXIT_FAILURE);
  }

  char *buf = malloc(BUFSIZE * sizeof(char));

  printf("Enter messages to send. Each line is a message:\n\n");

  while (1) {
    fgets(buf, BUFSIZE, stdin);
    write(socket_fd, buf, strlen(buf));
  }
}
