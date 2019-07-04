#include "event-handler.h"
#include <stdio.h>

char* action = "action";
char* message1 = "message1";
char* message2 = "message2";

void actionHandler(char* message) {
    printf("message: %s\n", message);
}

int main(int argc, char const *argv[])
{
    on(action, &actionHandler);
    emit(action, message1);
    emit(action, message2);
    return 0;
}
