#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (void){
    int fd;
    int numbytes;
    char path[] = "file";
    char buf[256];

    /*
     * O_CREAT:如果文件不存在则创建
     * O_RDONLY:以只读模式打开文件
     */
    fd = open(path, O_CREAT | O_RDONLY, 0644);
    printf("%d", fd);
    if(fd < 0){
        perror("open()");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0x00, 256);
    while((numbytes = read(fd, buf, 255)) > 0){
        printf("%d bytes read: %s", numbytes, buf);
        memset(buf, 0x00, 256);
    }
    close (fd);
    exit(EXIT_SUCCESS);
}