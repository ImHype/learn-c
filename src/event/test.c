#include "event-handler.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

char * action = "action";
char * action_for_linked_list_version = "action_for_linked_list_version";
char * action_for_struct_data = "action_for_struct_data";
char * message1 = "message1";
char * message2 = "message2";


void println() {
    printf("\n");
}

void action_handler(void* message) {
    printf("message from global_array_version: %s\n", (char*) message);
}

void action_handler_for_linked_list_version(void* message) {
    printf("message from linked_list_version: %s\n", (char*) message);
}

int test_global_array_version() {
    on(action, &action_handler);

    emit(action, message1);
    emit(action, message2);
    println();

    return 0;
}

int linked_list_version() {
    EventEmitter *eventEmitter = createEventEmitter();

    addEvent(eventEmitter, action_for_linked_list_version, &action_handler_for_linked_list_version);
    addEvent(eventEmitter, action_for_linked_list_version, &action_handler_for_linked_list_version);

    triggerEvent(eventEmitter, action_for_linked_list_version, message1);
    triggerEvent(eventEmitter, action_for_linked_list_version, message2);
    println();
    
    return 0;
}

typedef struct EventData
{
    char * name;
    char * message;
    int count;
} EventData;

void action_handler_for_struct_data(void* message) {
    EventData * data = ((EventData*) message);

    assert(strcmp(data->name, "hello") == 0);
    assert(strcmp(data->message, "我是一条消息") == 0);
    assert(data->count == 100);

    printf("message from action_handler_for_struct_data: %s\n", data -> name);
}

int transfer_structure_by_event_handler() {
    EventEmitter *eventEmitter = createEventEmitter();

    EventData * data = (EventData *) malloc(sizeof(EventData));

    data->name = "hello";
    data->message = "我是一条消息";
    data->count = 100;

    addEvent(eventEmitter, action_for_struct_data, &action_handler_for_struct_data);
    triggerEvent(eventEmitter, action_for_struct_data, data);

    return 0;
}

int main(int argc, char const *argv[])
{
    test_global_array_version();
    linked_list_version();
    transfer_structure_by_event_handler();
    return 0;
}