#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h> 

int socket_fd;

void graceful() {
    close(socket_fd);
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGHUP, graceful);
    signal(SIGINT, graceful);
    signal(SIGQUIT, graceful);

    struct sockaddr_in address;
    struct sockaddr_in cliaddr;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 

    printf("opened socket_fd: %d\n", socket_fd);

    int enable_reuse = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable_reuse, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9999);
    
    if (bind(socket_fd, (struct sockaddr*)&address,  sizeof(address)) < 0 ) {
        perror("bind");
        exit(1);
    };


    if (listen(socket_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    sleep(20);

    return 0;
}