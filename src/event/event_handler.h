#include "../hash_map/hash_map.h"
#include "../linked-list/linked-list.h"


#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
typedef struct event_emitter_s event_emitter_t;

typedef void (*handler_callback_t)(void*);
typedef int (*on_t)(event_emitter_t * event_emitter, char*, handler_callback_t);
typedef int (*emit_t)(event_emitter_t * event_emitter, char*, void*);

typedef struct {
    char * name;
    handler_callback_t callback;
} handler_t;

struct event_emitter_s
{
    hashmap_t * map;
    on_t on;
    emit_t emit;
} ;

int create_event_emitter(event_emitter_t * event_emitter);

int on(event_emitter_t * event_emitter, char*, handler_callback_t);
int emit(event_emitter_t * event_emitter, char*, void*);

#endif