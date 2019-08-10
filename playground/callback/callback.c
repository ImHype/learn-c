#include<stdio.h>

int callback(int (*callback)(), int i) {
    printf("this is the %d time\n", i);

    printf("do some async things\n");
    
    printf("excuting callback\n");

    int res = callback();

    printf("excuted callback\nresult is %d\n\n\n", res);
    return 0;
}


int callback2() {
    printf("callback2 is excuted\n");
    return 0;
}