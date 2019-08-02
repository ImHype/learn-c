#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "event_handler.h"


handler_t * create_handler(char* name, handler_callback_t callback) {
    handler_t * h = malloc(sizeof(handler_t));

    h->name = name;
    h->callback = callback;

    return h;
}

int on(event_emitter_t * event_emitter, char* name, handler_callback_t callback) {
    hashmap_t * map = event_emitter->map;
    linked_list_t * l = (linked_list_t *) map->get(map, name);

    if (l == NULL) {
        l = malloc(sizeof(linked_list_t));
        create_linked_list(l);

        map->put(map, name, l);
    }

    linked_list_add(l, create_handler(name, callback));

    return 0;
};


int emit(event_emitter_t * event_emitter, char* name, void* val) {
    hashmap_t * map = event_emitter->map;
    linked_list_t * l = (linked_list_t *) map->get(map, name);

    if (l == NULL) {
        return -1;
    }

    handler_t * it;

    LIST_FOREACH_BEGIN(l, it)
        it->callback(val);
    LIST_FOREACH_END;

    return 0;
};


int create_event_emitter(event_emitter_t * event_emitter) {
    event_emitter->map = malloc(sizeof(event_emitter_t));
    hash_map_init(event_emitter->map);
    event_emitter->on = on;
    event_emitter->emit = emit;
    return 0;
}
