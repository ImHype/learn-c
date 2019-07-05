typedef void (*Callback)(char* message);


typedef struct Handler {
    char *name;
    Callback cb;
} Handler;

typedef struct LinkedList {
    Handler * handler;
    struct LinkedList *next;
} LinkedList;

typedef LinkedList EventEmitter;

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#define MAX_NAME_LENGTH 10;

EventEmitter *createEventEmitter();
void on(char* name, Callback cb);
void emit(char* name, char* message);
void addEvent(EventEmitter *eventEmitter, char * name, Callback callback);
void triggerEvent(EventEmitter *eventEmitter, char * name, char * message);

#endif