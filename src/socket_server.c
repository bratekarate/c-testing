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
    int bind_res = bind(socket_fd, (struct sockaddr *) &addr, len);
    printf("bind result: %d\n", bind_res);
    int listen_res = listen(socket_fd, 1);
    printf("listen result: %d\n", listen_res);
    int acc_res = accept(socket_fd, (struct sockaddr *) &addr, &len);
    printf("accept result: %d\n", acc_res);

    char * out = malloc(10 * sizeof(char));
    read(acc_res, out, 10);
    printf("%s\n", out);

}
