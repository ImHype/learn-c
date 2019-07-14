#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h> 


int main(int argc, char const *argv[])
{
    int server_fd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;

    int clientfd, ret;

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(9999);

    bind(server_fd, (struct sockaddr*)&servaddr,  sizeof(servaddr));
    printf("fd: %d\n", server_fd);
    ret = listen(server_fd, 5); 


    // while (1)
    // {
        printf("OK\n");
        clientfd = accept(server_fd, (struct sockaddr*)&cliaddr, &cliaddrlen);
        printf("accept%d\n", cliaddrlen);

        cliaddrlen = sizeof(cliaddr);
        ret = getsockname(clientfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
        if (ret < 0) perror("getsockaddr");
        printf("sockaddr: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        // 7. send data
        write(clientfd, "Hello wolrd!\n", 13);
        close(clientfd);
    // }

    close(server_fd);
    
    return 0;
}
