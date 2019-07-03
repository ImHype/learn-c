#include<string.h>
#include<stdio.h>
#include "event-handler.h"


callback* globalCb;

void on(callback* cb) {
    globalCb = cb;
};


void emit() {
    (*globalCb)();
};