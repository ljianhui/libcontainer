#ifndef _C_DEQUE_H
#define _C_DEQUE_H

#include "c_libdef.h"

typedef struct c_deque c_deque;

c_deque* c_deque_create(dump_func dump, release_func release, size_t elem_size);
c_deque* c_deque_clone(const c_deque *src);
void c_deque_destroy(c_deque *deq);

void* c_deque_add_first(c_deque *deq, const void *elem);
void* c_deque_add_last(c_deque *deq, const void *elem);

int c_deque_remove_first(c_deque *deq);
int c_deque_remove_last(c_deque *deq);

void c_deque_clear(c_deque *deq);

void* c_deque_get_first(const c_deque *deq);
void* c_deque_get_last(const c_deque *deq);

int c_deque_is_empty(const c_deque *deq);
int c_deque_size(const c_deque *deq);

#endif
