#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#inclued "libdef.h"

typedef struct priority_queue priority_queue;

priority_queue* priority_queue_create(size_t elem_size, compare_func comparator);
void priority_queue_destroy(priority_queue *pri_queue);

int priority_queue_push(priority_queue *pri_queue, const void *elem);
void priority_queue_pop(priority_queue *pri_queue);
void priority_queue_clear(priority_queue *pri_queue);

void* priority_queue_top(priority_queue *pri_queue);
int priority_queue_size(priority_queue *pri_queue);
int priority_queue_is_empty(priority_queue *pri_queue);

#endif
