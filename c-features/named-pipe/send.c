#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buf[] = "hello";
    char buf2[] = "world";

    mkfifo("1.pipe", 0664);
    mkfifo("2.pipe", 0664);

    int fd = open("1.pipe", O_WRONLY);
    int fd2 = open("2.pipe", O_WRONLY);


    while (1)
    {
        write(fd2, buf2, strlen(buf2) + 1);
        sleep(5);
        write(fd, buf, strlen(buf) + 1);
    }
    
    return 0;
}
