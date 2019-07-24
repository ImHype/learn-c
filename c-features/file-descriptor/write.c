#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char * str = "hello \n";

    int fd = open("hello.txt", O_WRONLY | O_CREAT, 0666);

    if (fd < 0) {
        perror("err1");
    }

    if (write(fd, str, strlen(str)) < 0) {
        perror("err2");
    };

    return 0;
}
