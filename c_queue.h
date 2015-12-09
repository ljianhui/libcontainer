#ifndef _C_QUEUE_H
#define _C_QUEUE_H

#include "c_libdef.h"

typedef struct c_deque c_queue;

c_queue* c_queue_create(size_t elem_size);
c_queue* c_queue_clone(const c_queue *q);
void c_queue_destroy(c_queue *q);

void* c_queue_push(c_queue *q, const void *elem);
void c_queue_pop(c_queue *q);
void* c_queue_top(const c_queue *q);
void c_queue_clear(c_queue *q);

int c_queue_is_empty(const c_queue *q);
int c_queue_size(const c_queue *q);

#endif
