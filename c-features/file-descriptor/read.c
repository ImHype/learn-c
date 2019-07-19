#include<unistd.h> 
#include<string.h> 
#include<stdio.h> 

int main(int argc, char const *argv[])
{
    char str2[3];
    read(0, str2, 3);

    printf("%s", str2);
    return 0;
}
