#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buf[64];

    mkfifo("1.pipe", 0664);
    mkfifo("2.pipe", 0664);

    int n;

    int openstatus[] = {1, 1};
    int openedfd[2];
    openedfd[0] = open("1.pipe", O_RDONLY);
    openedfd[1] = open("2.pipe", O_RDONLY);
    
    while (openstatus[0] || openstatus[1])
    {
        if (openstatus[0]) {
            n = read(openedfd[0], buf, 64);

            if (n == 0) {
                printf("remote end closed\n");
                openstatus[0] = 0;
            } else {
                printf("fd recieve: %s\n", buf);
            }
        }

        if (openstatus[1]) {
            n = read(openedfd[1], buf, 64);

            if (n == 0) {
                printf("remote end closed\n");
                openstatus[1] = 0;
            } else {
                printf("fd recieve: %s\n", buf);
            }
        }
    }
    
    return 0;
}
