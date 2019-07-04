#include<string.h>
#include<stdio.h>
#include "event-handler.h"
#define MAX_SIZE 100

int crt = 0;

Handler handlers[MAX_SIZE];

void on(char* name, Callback cb) {
    Handler handler;
    handler.name = name;
    handler.cb = cb;

    handlers[crt] = handler;
    crt++;
};

void emit(char* name, char* message) {
    for (int i = 0; i < MAX_SIZE; i++)
    {
        Handler handler = handlers[i];
        if (!handler.name) {
            break;
        }
        if (strcmp(handler.name, name) == 0) {
            handler.cb(message);
        }
    }
};