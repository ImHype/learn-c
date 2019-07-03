#include <assert.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 1;
    char b = 'h';

    // only one usage, like:
    // assert(expression);

    assert(a > 0);
    assert(b == 'h');

    printf("hello world\n");
    return 0;
}