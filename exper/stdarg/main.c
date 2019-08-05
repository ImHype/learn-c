#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int println(const char *fmt, ...)
{
    char printf_buf[1024];
    va_list args;
    int printed;
    va_start(args, fmt);
    printed = vsprintf(printf_buf, fmt, args);
    va_end(args);
    puts(printf_buf);
    return printed;
}


int sum(int n, ...)
{
    va_list ap;
    va_start(ap, n);

    int res = 0;
    while(n--)
        res += va_arg(ap, int);

    va_end(ap);
    return res;
}

int main()
{
    int res = sum(1, 3, 4);
    char * a = "kkk你好kkk";

    printf("%lu", sizeof(*a));
    printf("%d\n", res);
    println("你好");
    return 0;
}