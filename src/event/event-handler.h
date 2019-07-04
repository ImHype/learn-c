typedef void (*Callback)(char* message);

typedef struct Handler {
    char *name;
    Callback cb;
    struct Handler *next;
} Handler;

typedef struct EventEmitter {
    struct Handler *handler;
} EventEmitter;

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#define MAX_NAME_LENGTH 10;

void on(char* name, Callback cb);
void emit(char* name, char* message);

#endif