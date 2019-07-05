#include <stdlib.h>
#include<string.h>
#include<stdio.h>

#include "event-handler.h"


Handler * createHandler(char * name, Callback callback) {
    Handler *handler = (Handler*) malloc(sizeof(Handler));
    handler->name = name;
    handler->cb = callback;
    return handler;
}

EventEmitter *createEventEmitter() {
    EventEmitter *eventEmitter = (EventEmitter*) malloc(sizeof(EventEmitter));
    eventEmitter->data = NULL;
    eventEmitter->next = NULL;
    return eventEmitter;
};

void addEvent(EventEmitter *eventEmitter, char * name, Callback callback) {
    Handler * handler = createHandler(name, callback);
    if (eventEmitter->data == NULL) {
        eventEmitter->data = handler;
    } else {
        EventEmitter * thisEventEmitter = createEventEmitter();
        thisEventEmitter->data = handler;
        while (eventEmitter->next != NULL)
        {
            eventEmitter = eventEmitter->next;
        }
        eventEmitter->next = thisEventEmitter;
    }
}

void triggerEvent(EventEmitter *eventEmitter, char * name, void * message) {
    Handler * handler = eventEmitter -> data;

    while (eventEmitter != NULL)
    {
        Handler * handler = eventEmitter->data;
        if (strcmp(handler->name, name) == 0) {
            (handler->cb)(message);
        }

        if (eventEmitter->next != NULL) {
            eventEmitter = eventEmitter->next;
        } else {
            break;
        }
    }
}