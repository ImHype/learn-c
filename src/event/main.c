#include "event-handler.h"
#include <stdio.h>

char* action = "action";
char* action_for_linked_list_version = "action";
char* message1 = "message1";
char* message2 = "message2";

void action_handler(char* message) {
    printf("message from global_array_version: %s\n", message);
}

void action_handler_for_linked_list_version(char* message) {
    printf("message from linked_list_version: %s\n", message);

}

int global_array_version() {
    on(action, &action_handler);
    emit(action, message1);
    emit(action, message2);
    return 0;
}


int linked_list_version() {
     EventEmitter *eventEmitter;
    eventEmitter = createEventEmitter();

    addEvent(eventEmitter, action_for_linked_list_version, &action_handler_for_linked_list_version);
    triggerEvent(eventEmitter, action_for_linked_list_version, message1);
    triggerEvent(eventEmitter, action_for_linked_list_version, message2);

    return 0;
}

int main(int argc, char const *argv[])
{
    global_array_version();
    linked_list_version();
    return 0;
}


