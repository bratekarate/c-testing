#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {

    int socket_fd;

    if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    struct sockaddr_un addr;
    memset(&addr, '\0', sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/mysock", sizeof(addr.sun_path));

    socklen_t len = sizeof(struct sockaddr_un);
    int con_res = connect(socket_fd, (struct sockaddr *) &addr, len);
    printf("connect result: %d\n", con_res);
    char * buf = "Hallo Wel";
    write(socket_fd, buf, 10);
}
