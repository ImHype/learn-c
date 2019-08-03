#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    char str[1024];
    int fd = open("hello.txt", O_RDONLY, 0666);
    read(fd, str, sizeof(str));
    close(fd);
    printf("%s\n", str);
    return 0;
}