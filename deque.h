#ifndef _DEQUE_H
#define _DEQUE_H

typedef struct deque deque;

deque* deque_create(size_t elem_size);
deque* deque_clone(const deque *src);
void deque_destroy(deque *deq);

void* deque_add_first(deque *deq, const void *elem);
void* deque_add_last(deque *deq, const void *elem);

int deque_remove_first(deque *deq);
int deque_remove_last(deque *deq);

void deque_clear(deque *deq);

void* deque_get_first(const deque *deq);
void* deque_get_last(const deque *deq);

int deque_is_empty(const deque *deq);
int deque_size(const deque *deq);

#endif