typedef void callback();

typedef struct Handler {
    char *name;
    callback *cb;
    struct Handler *next;
} Handler;

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#define MAX_NAME_LENGTH 10;

void on(callback* cb);
void emit();

#endif