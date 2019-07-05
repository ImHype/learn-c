typedef void (*Callback)(void*);


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
void on(char*, Callback);
void emit(char*, char*);
void addEvent(EventEmitter *, char *, Callback);
void triggerEvent(EventEmitter *, char* , void *);

#endif