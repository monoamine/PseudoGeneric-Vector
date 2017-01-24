#pragma once

#include <stddef.h>

#define DEFAULT_CAPACITY 10

typedef struct Vector
{
    void* items;
    size_t itemsize;
    size_t size;
    size_t capacity;
} Vector;

typedef void (*vec_func)(const void* item);

inline void vector_new(Vector* v, size_t itemsize);
void vector_new1(Vector* v, size_t itemsize, size_t capacity);
void vector_delete(Vector* v);

bool vector_empty(Vector* v);
size_t vector_size(Vector* v);

void* vector_at(Vector* v, size_t idx);
void vector_set(Vector* v, size_t idx, const void* value);

void vector_reserve(Vector* v, size_t new_capacity);
void vector_push_back(Vector* v, const void* value);
void vector_pop_back(Vector* v, void* dest);

void vector_for_each(Vector* v, vec_func func);
void vector_assign(Vector* v, size_t itemsize, size_t count, const void* value);
