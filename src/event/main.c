#include "event-handler.h"
#include <stdio.h>

void helloCallback() {
    printf("hello\n");
}

int main(int argc, char const *argv[])
{
    on(&helloCallback);
    emit();
    emit();
    emit();
    emit();
    return 0;
}
