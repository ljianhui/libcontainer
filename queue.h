#ifndef _QUEUE_H
#define _QUEUE_H

#include "libdef.h"

typedef struct deque queue;

queue* queue_create(size_t elem_size);
queue* queue_clone(const queue *q);
void queue_destroy(queue *q);

void* queue_push(queue *q, const void *elem);
void queue_pop(queue *q);
void* queue_top(const queue *q);
void queue_clear(queue *q);

int queue_is_empty(const queue *q);
int queue_size(const queue *q);

#endif
