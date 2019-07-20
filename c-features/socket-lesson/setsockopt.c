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

    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 

    printf("opened socket_fd: %d\n", socket_fd);

    int enable_reuse = 1;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable_reuse, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    sleep(10);

    return 0;
}