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
    LinkedList *eventEmitter = (LinkedList*) malloc(sizeof(LinkedList));
    eventEmitter->handler = NULL;
    eventEmitter->next = NULL;
    return eventEmitter;
};

void addEvent(EventEmitter *eventEmitter, char * name, Callback callback) {
    Handler * handler = createHandler(name, callback);
    if (eventEmitter->handler == NULL) {
        eventEmitter->handler = handler;
    } else {
        EventEmitter * thisEventEmitter = createEventEmitter();
        thisEventEmitter->handler = handler;
        while (eventEmitter->next != NULL)
        {
            eventEmitter = eventEmitter->next;
        }
        eventEmitter->next = thisEventEmitter;
    }
}

void triggerEvent(EventEmitter *eventEmitter, char * name, void * message) {
    Handler * handler = eventEmitter -> handler;

    while (eventEmitter != NULL)
    {
        if (strcmp(eventEmitter->handler->name, name) == 0) {
            (eventEmitter->handler->cb)(message);
        }

        if (eventEmitter->next != NULL) {
            eventEmitter = eventEmitter->next;
        } else {
            break;
        }
    }
}