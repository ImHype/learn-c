#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h> 

int socket_fd;
struct sockaddr_in address;
struct sockaddr_in cliaddr;

socklen_t cliaddrlen;
socklen_t seraddrlen;


void graceful() {
    close(socket_fd);
    exit(0);
}

char * response = "HTTP/1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nConnection: keep-alive\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" /><title>Document</title></head><body><p>this is http response</p></body></html>";


void* thread_main(void* argv) {
    while (1)
    {
        int client_fd, ret;
        client_fd = accept(socket_fd, (struct sockaddr*)&cliaddr, &cliaddrlen);

        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        cliaddrlen = sizeof(cliaddr);

        char buf[1000];

        read(client_fd, buf, sizeof(buf));


        if (write(client_fd, response, strlen(response)) < 0) {
            perror("write");
        }

        if (shutdown(client_fd, SHUT_RDWR) < 0) {
            printf("client_fd: %d", client_fd);
            perror("shutdown");
        };

        int size = read(client_fd, buf, sizeof(buf));

        if (size == 0) {
            if (close(client_fd) < 0) {
                perror("close");
            }
        } else if (size < 0) {
            perror("read");
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    signal(SIGHUP, graceful);
    signal(SIGINT, graceful);
    signal(SIGQUIT, graceful);

    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 

    printf("opened socket_fd: %d\n", socket_fd);

    int enable_reuse = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable_reuse, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(9999);
    
    if (bind(socket_fd, (struct sockaddr*)&address,  sizeof(address)) < 0 ) {
        perror("bind");
        exit(1);
    };

    if (listen(socket_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    pthread_t threads[4];

    for (int i = 0; i < 4; i++)
    {
        void *status;            
        pthread_create(&threads[i], NULL, thread_main, NULL);
        pthread_join(threads[i], status);
    }

    return 0;
}
