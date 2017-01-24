#include "vector.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


void vector_new(Vector* v, size_t itemsize)
{
    vector_new1(v, itemsize, DEFAULT_CAPACITY);
}

void vector_new1(Vector* v, size_t itemsize, size_t capacity)
{
    v->items = malloc(itemsize * capacity);

    v->itemsize = itemsize;
    v->capacity = capacity;
    v->size = 0;
}

void vector_delete(Vector* v)
{
    free(v->items);
}

bool vector_empty(Vector* v)
{
    return v->size == 0;
}

size_t vector_size(Vector* v)
{
    return v->size;
}

void* vector_at(Vector* v, size_t idx)
{
    assert(idx < v->size);

    void* item = (char *)v->items + (idx * v->itemsize);
    return item;
}

void vector_set(Vector* v, size_t idx, const void* value)
{
    assert(idx < v->size);

    void* item = vector_at(v, idx);
    memcpy(item, value, v->itemsize);
}

void vector_reserve(Vector* v, size_t new_capacity)
{
    if (new_capacity <= v->capacity) return;

    v->items = realloc(v->items, new_capacity);
    v->capacity *= 2;
}

void vector_push_back(Vector* v, const void* value)
{
    if (v->size == v->capacity)
        vector_reserve(v,v->capacity * 2);

    vector_set(v, ++v->size, value);
}

void vector_pop_back(Vector* v, void* dest)
{
    if (vector_empty(v)) return;

    const void* src = vector_at(v, --v->size);
    memcpy(dest, src, v->itemsize);
}

void vector_for_each(Vector* v, vec_func func)
{
    for (size_t i = 0; i < v->size; ++i)
        func(vector_at(v, i));
}

void vector_for_each_of(Vector* v, size_t from, size_t to, vec_func func)
{
    assert(to >= 0 && from >= 0);
    assert(to < v->size && from < v->size);

    if (to >= from)
    {
        for (int i = from; i <= to; ++i)
            func(vector_at(v, i));
    }
    else
    {
        for (int i = from; i >= to; --i)
            func(vector_at(v, i));
    }
}

void vector_assign(Vector* v, size_t itemsize, size_t count, const void* value)
{
    vector_new1(v, itemsize, count);
    v->size = count;
    
    for (size_t i = 0; i < count; ++i)
        vector_set(v, i, value);
}
