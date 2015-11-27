#ifndef _MKY_DEQUE_H
#define _MKY_DEQUE_H

#include "mky_libdef.h"

typedef struct mky_deque mky_deque;

mky_deque* mky_deque_create(size_t elem_size);
mky_deque* mky_deque_clone(const mky_deque *src);
void mky_deque_destroy(mky_deque *deq);

void* mky_deque_add_first(mky_deque *deq, const void *elem);
void* mky_deque_add_last(mky_deque *deq, const void *elem);

int mky_deque_remove_first(mky_deque *deq);
int mky_deque_remove_last(mky_deque *deq);

void mky_deque_clear(mky_deque *deq);

void* mky_deque_get_first(const mky_deque *deq);
void* mky_deque_get_last(const mky_deque *deq);

int mky_deque_is_empty(const mky_deque *deq);
int mky_deque_size(const mky_deque *deq);

#endif
