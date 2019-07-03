#include <stdio.h>

int callback();
int callback2();

int main(int argc, char const *argv[])
{

    int i = 0;
    // 这两种操作是等价的，都会将函数指针传入
    callback(callback2, i++);

    callback(&callback2, i++);
    printf("hello world");
    return 0;
}
