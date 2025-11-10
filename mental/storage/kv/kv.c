// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "kv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Hash function
static unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

KVStore* kv_create(size_t capacity) {
    KVStore* store = malloc(sizeof(KVStore));
    if (!store) return NULL;
    
    store->capacity = capacity > 0 ? capacity : 64;
    store->size = 0;
    store->buckets = calloc(store->capacity, sizeof(KeyValue*));
    
    if (!store->buckets) {
        free(store);
        return NULL;
    }
    
    return store;
}

void kv_destroy(KVStore* store) {
    if (!store) return;
    
    kv_clear(store);
    free(store->buckets);
    free(store);
}

bool kv_put_string(KVStore* store, const char* key, const char* value) {
    if (!store || !key || !value) return false;
    if (strlen(key) >= MAX_KEY_LENGTH) return false;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    // Check if key already exists
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value.type = KV_TYPE_STRING;
            strncpy(current->value.value.string_value, value, MAX_VALUE_SIZE - 1);
            current->value.value.string_value[MAX_VALUE_SIZE - 1] = '\0';
            return true;
        }
        current = current->next;
    }
    
    // Create new key-value pair
    KeyValue* new_kv = malloc(sizeof(KeyValue));
    if (!new_kv) return false;
    
    strncpy(new_kv->key, key, MAX_KEY_LENGTH - 1);
    new_kv->key[MAX_KEY_LENGTH - 1] = '\0';
    
    new_kv->value.type = KV_TYPE_STRING;
    strncpy(new_kv->value.value.string_value, value, MAX_VALUE_SIZE - 1);
    new_kv->value.value.string_value[MAX_VALUE_SIZE - 1] = '\0';
    
    new_kv->next = store->buckets[index];
    store->buckets[index] = new_kv;
    store->size++;
    
    return true;
}

bool kv_put_int(KVStore* store, const char* key, int value) {
    if (!store || !key) return false;
    if (strlen(key) >= MAX_KEY_LENGTH) return false;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value.type = KV_TYPE_INT;
            current->value.value.int_value = value;
            return true;
        }
        current = current->next;
    }
    
    KeyValue* new_kv = malloc(sizeof(KeyValue));
    if (!new_kv) return false;
    
    strncpy(new_kv->key, key, MAX_KEY_LENGTH - 1);
    new_kv->key[MAX_KEY_LENGTH - 1] = '\0';
    
    new_kv->value.type = KV_TYPE_INT;
    new_kv->value.value.int_value = value;
    
    new_kv->next = store->buckets[index];
    store->buckets[index] = new_kv;
    store->size++;
    
    return true;
}

bool kv_put_double(KVStore* store, const char* key, double value) {
    if (!store || !key) return false;
    if (strlen(key) >= MAX_KEY_LENGTH) return false;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value.type = KV_TYPE_DOUBLE;
            current->value.value.double_value = value;
            return true;
        }
        current = current->next;
    }
    
    KeyValue* new_kv = malloc(sizeof(KeyValue));
    if (!new_kv) return false;
    
    strncpy(new_kv->key, key, MAX_KEY_LENGTH - 1);
    new_kv->key[MAX_KEY_LENGTH - 1] = '\0';
    
    new_kv->value.type = KV_TYPE_DOUBLE;
    new_kv->value.value.double_value = value;
    
    new_kv->next = store->buckets[index];
    store->buckets[index] = new_kv;
    store->size++;
    
    return true;
}

bool kv_put_bool(KVStore* store, const char* key, bool value) {
    if (!store || !key) return false;
    if (strlen(key) >= MAX_KEY_LENGTH) return false;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value.type = KV_TYPE_BOOL;
            current->value.value.bool_value = value;
            return true;
        }
        current = current->next;
    }
    
    KeyValue* new_kv = malloc(sizeof(KeyValue));
    if (!new_kv) return false;
    
    strncpy(new_kv->key, key, MAX_KEY_LENGTH - 1);
    new_kv->key[MAX_KEY_LENGTH - 1] = '\0';
    
    new_kv->value.type = KV_TYPE_BOOL;
    new_kv->value.value.bool_value = value;
    
    new_kv->next = store->buckets[index];
    store->buckets[index] = new_kv;
    store->size++;
    
    return true;
}

bool kv_put_binary(KVStore* store, const char* key, const void* data, size_t size) {
    if (!store || !key || !data || size == 0) return false;
    if (strlen(key) >= MAX_KEY_LENGTH) return false;
    if (size > MAX_VALUE_SIZE) return false; // For simplicity
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Free existing binary data if any
            if (current->value.type == KV_TYPE_BINARY && current->value.value.binary.data) {
                free(current->value.value.binary.data);
            }
            current->value.type = KV_TYPE_BINARY;
            current->value.value.binary.data = malloc(size);
            if (!current->value.value.binary.data) return false;
            memcpy(current->value.value.binary.data, data, size);
            current->value.value.binary.size = size;
            return true;
        }
        current = current->next;
    }
    
    KeyValue* new_kv = malloc(sizeof(KeyValue));
    if (!new_kv) return false;
    
    strncpy(new_kv->key, key, MAX_KEY_LENGTH - 1);
    new_kv->key[MAX_KEY_LENGTH - 1] = '\0';
    
    new_kv->value.type = KV_TYPE_BINARY;
    new_kv->value.value.binary.data = malloc(size);
    if (!new_kv->value.value.binary.data) {
        free(new_kv);
        return false;
    }
    memcpy(new_kv->value.value.binary.data, data, size);
    new_kv->value.value.binary.size = size;
    
    new_kv->next = store->buckets[index];
    store->buckets[index] = new_kv;
    store->size++;
    
    return true;
}

const KVValue* kv_get(const KVStore* store, const char* key) {
    if (!store || !key) return NULL;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return &current->value;
        }
        current = current->next;
    }
    
    return NULL;
}

const char* kv_get_string(const KVStore* store, const char* key, const char* default_value) {
    const KVValue* value = kv_get(store, key);
    if (!value || value->type != KV_TYPE_STRING) return default_value;
    return value->value.string_value;
}

int kv_get_int(const KVStore* store, const char* key, int default_value) {
    const KVValue* value = kv_get(store, key);
    if (!value || value->type != KV_TYPE_INT) return default_value;
    return value->value.int_value;
}

double kv_get_double(const KVStore* store, const char* key, double default_value) {
    const KVValue* value = kv_get(store, key);
    if (!value || value->type != KV_TYPE_DOUBLE) return default_value;
    return value->value.double_value;
}

bool kv_get_bool(const KVStore* store, const char* key, bool default_value) {
    const KVValue* value = kv_get(store, key);
    if (!value || value->type != KV_TYPE_BOOL) return default_value;
    return value->value.bool_value;
}

const void* kv_get_binary(const KVStore* store, const char* key, size_t* size) {
    const KVValue* value = kv_get(store, key);
    if (!value || value->type != KV_TYPE_BINARY) {
        if (size) *size = 0;
        return NULL;
    }
    if (size) *size = value->value.binary.size;
    return value->value.binary.data;
}

KVType kv_get_type(const KVStore* store, const char* key) {
    const KVValue* value = kv_get(store, key);
    if (!value) return KV_TYPE_STRING; // Default or use an error value
    return value->type;
}

bool kv_delete(KVStore* store, const char* key) {
    if (!store || !key) return false;
    
    unsigned long index = hash(key) % store->capacity;
    KeyValue* current = store->buckets[index];
    KeyValue* prev = NULL;
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                store->buckets[index] = current->next;
            }
            
            // Free binary data if needed
            if (current->value.type == KV_TYPE_BINARY && current->value.value.binary.data) {
                free(current->value.value.binary.data);
            }
            
            free(current);
            store->size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    
    return false;
}

bool kv_exists(const KVStore* store, const char* key) {
    return kv_get(store, key) != NULL;
}

size_t kv_size(const KVStore* store) {
    return store ? store->size : 0;
}

void kv_clear(KVStore* store) {
    if (!store) return;
    
    for (size_t i = 0; i < store->capacity; i++) {
        KeyValue* current = store->buckets[i];
        while (current) {
            KeyValue* next = current->next;
            if (current->value.type == KV_TYPE_BINARY && current->value.value.binary.data) {
                free(current->value.value.binary.data);
            }
            free(current);
            current = next;
        }
        store->buckets[i] = NULL;
    }
    store->size = 0;
}

void kv_print_all(const KVStore* store) {
    if (!store) return;
    
    printf("Key-Value Store (%zu items):\n", store->size);
    for (size_t i = 0; i < store->capacity; i++) {
        KeyValue* current = store->buckets[i];
        while (current) {
            const char* type_str;
            char value_str[128];
            
            switch (current->value.type) {
                case KV_TYPE_STRING:
                    type_str = "STRING";
                    snprintf(value_str, sizeof(value_str), "\"%s\"", current->value.value.string_value);
                    break;
                case KV_TYPE_INT:
                    type_str = "INT";
                    snprintf(value_str, sizeof(value_str), "%d", current->value.value.int_value);
                    break;
                case KV_TYPE_DOUBLE:
                    type_str = "DOUBLE";
                    snprintf(value_str, sizeof(value_str), "%.2f", current->value.value.double_value);
                    break;
                case KV_TYPE_BOOL:
                    type_str = "BOOL";
                    snprintf(value_str, sizeof(value_str), "%s", current->value.value.bool_value ? "true" : "false");
                    break;
                case KV_TYPE_BINARY:
                    type_str = "BINARY";
                    snprintf(value_str, sizeof(value_str), "[%zu bytes]", current->value.value.binary.size);
                    break;
                default:
                    type_str = "UNKNOWN";
                    strcpy(value_str, "?");
            }
            
            printf("  %s (%s): %s\n", current->key, type_str, value_str);
            current = current->next;
        }
    }
}

// Note: File persistence would need to handle different types
// This is a simplified version that only handles strings for demonstration
bool kv_save_to_file(const KVStore* store, const char* filename) {
    // Implementation would need to handle all types
    // For now, just save string values
    (void)store;
    (void)filename;
    return false; // Placeholder
}

bool kv_load_from_file(KVStore* store, const char* filename) {
    // Implementation would need to handle all types
    // For now, just load string values
    (void)store;
    (void)filename;
    return false; // Placeholder
}
