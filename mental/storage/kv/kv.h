#ifndef KV_STORE_TYPED_H
#define KV_STORE_TYPED_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_SIZE 1024

typedef enum {
    KV_TYPE_STRING,
    KV_TYPE_INT,
    KV_TYPE_DOUBLE,
    KV_TYPE_BINARY,
    KV_TYPE_BOOL
} KVType;

typedef struct {
    KVType type;
    union {
        char string_value[MAX_VALUE_SIZE];
        int int_value;
        double double_value;
        bool bool_value;
        struct {
            void* data;
            size_t size;
        } binary;
    } value;
} KVValue;

typedef struct KeyValue {
    char key[MAX_KEY_LENGTH];
    KVValue value;
    struct KeyValue* next;
} KeyValue;

typedef struct {
    KeyValue** buckets;
    size_t capacity;
    size_t size;
} KVStore;

// Initialize and cleanup
KVStore* kv_create(size_t capacity);
void kv_destroy(KVStore* store);

// Type-specific put operations
bool kv_put_string(KVStore* store, const char* key, const char* value);
bool kv_put_int(KVStore* store, const char* key, int value);
bool kv_put_double(KVStore* store, const char* key, double value);
bool kv_put_bool(KVStore* store, const char* key, bool value);
bool kv_put_binary(KVStore* store, const char* key, const void* data, size_t size);

// Generic get operation (returns type information)
const KVValue* kv_get(const KVStore* store, const char* key);

// Type-specific get operations with error checking
const char* kv_get_string(const KVStore* store, const char* key, const char* default_value);
int kv_get_int(const KVStore* store, const char* key, int default_value);
double kv_get_double(const KVStore* store, const char* key, double default_value);
bool kv_get_bool(const KVStore* store, const char* key, bool default_value);
const void* kv_get_binary(const KVStore* store, const char* key, size_t* size);

// Other operations
bool kv_delete(KVStore* store, const char* key);
bool kv_exists(const KVStore* store, const char* key);
size_t kv_size(const KVStore* store);
void kv_clear(KVStore* store);
void kv_print_all(const KVStore* store);

// Persistence
bool kv_save_to_file(const KVStore* store, const char* filename);
bool kv_load_from_file(KVStore* store, const char* filename);

// Utility functions
KVType kv_get_type(const KVStore* store, const char* key);

#endif
