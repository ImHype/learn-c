#include "event_handler.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

char * action = "action";
char * action_for_linked_list_version = "action_for_linked_list_version";
char * action_for_struct_data = "action_for_struct_data";
char * message1 = "message1";
char * message2 = "message2";

typedef struct
{
    char * from;
    char * message;
    int count;
} event_data_t;

void println() {
    printf("\n");
}

void action_handler(void* message) {
    printf("message from global_array_version: %s\n", (char*) message);
}

void action_handler2(void* message) {
    event_data_t * event_data = (event_data_t*) message;

    printf("message from %s: %s\n", event_data->from, event_data->message);
}


int main(int argc, char const *argv[])
{
    event_emitter_t event_emitter;
    event_emitter_t * p = &event_emitter;

    create_event_emitter(p);
    event_data_t event_data;
    event_data.from = "hello";
    event_data.message = "world";
    event_data.count = 0;

    p->on(p, action, action_handler);
    p->on(p, action_for_struct_data, action_handler2);

    p->emit(p, action, message1);
    p->emit(p, action_for_struct_data, &event_data);
    p->emit(p, action_for_struct_data, &event_data);
    p->emit(p, action_for_struct_data, &event_data);
    p->emit(p, action_for_struct_data, &event_data);

    p->emit(p, action, message1);
    p->emit(p, action, message1);
    p->emit(p, action, message1);
    
    return 0;
}