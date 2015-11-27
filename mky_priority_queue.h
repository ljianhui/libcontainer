#ifndef _MKY_PRIORITY_QUEUE_H
#define _MKY_PRIORITY_QUEUE_H

#include "mky_libdef.h"

typedef struct mky_priority_queue mky_priority_queue;

mky_priority_queue* mky_priority_queue_create(size_t elem_size, compare_func comparator);
mky_priority_queue* mky_priority_queue_clone(const mky_priority_queue *src);
void mky_priority_queue_destroy(mky_priority_queue *pri_queue);

const void* mky_priority_queue_push(mky_priority_queue *pri_queue, const void *elem);
void mky_priority_queue_pop(mky_priority_queue *pri_queue);
void mky_priority_queue_clear(mky_priority_queue *pri_queue);

const void* mky_priority_queue_top(mky_priority_queue *pri_queue);
int mky_priority_queue_size(mky_priority_queue *pri_queue);
int mky_priority_queue_is_empty(mky_priority_queue *pri_queue);

#endif
