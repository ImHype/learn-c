#include <stdio.h>

union var {
    char * hello2;
    char * hello1;
    char * hello;
};

/**
 * 使用共用体，可以修改 union 中的任何一个值，其他值复用其值的操作，
 */

int main(int argc, char const *argv[])
{
    union var v;
    v.hello = "nihaohao a a a a a";

    printf("v.l is %s\n", v.hello1);
    printf("v.l is %s\n", v.hello2);
    v.hello1 = "1";
    printf("v.l is %s\n", v.hello);
    printf("v.l is %s\n", v.hello2);
    return 0;
}
