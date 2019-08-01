#ifndef HASH_MAP_H

#define HASH_MAP_H

typedef struct hash_map_s hashmap_t;
typedef struct hashentry_s hashentry_t;


typedef int (*put_t)(hashmap_t * hash_map, void * key, void * val);
typedef void * (*get_t)(hashmap_t * hash_map, void * key);
typedef int (*del_t)(hashmap_t * hash_map, void * key);
typedef int (*hashcode_t)(hashmap_t * hash_map, void * key);
typedef int (*isempty_t)(hashmap_t * hash_map);
typedef int (*scale_t)(hashmap_t * hash_map);
typedef int (*callback_t)(void *key, void * value);

typedef int (*foreach_t)(hashmap_t* hashmap, callback_t callback);
typedef void ** (*keys_t)(hashmap_t* hashmap);

struct hashentry_s
{
    void * key;
    void * value;

    hashentry_t * next;
};


struct hash_map_s {
    hashentry_t ** hashentry;

    int size;           // 当前大小
    int buckets;       // 有效空间大小
    float resize_value;       // 有效空间大小

    hashcode_t hashcode;
    put_t put;
    get_t get;
    del_t del;
    scale_t scale;
    foreach_t foreach;
    keys_t keys;

    isempty_t isempty;
};

int hashcode(hashmap_t * hash_map, void * key);
int hash_map_init(hashmap_t * hash_map);
int hash_map_put(hashmap_t * hash_map, void * key, void * value);
void * hash_map_get(hashmap_t * hash_map, void * key);
int hash_map_delete(hashmap_t * hash_map, void * key);
int hash_map_foreach(hashmap_t* hashmap, callback_t callback);
void ** hash_map_keys(hashmap_t* hashmap);

#endif