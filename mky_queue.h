#ifndef _MKY_QUEUE_H
#define _MKY_QUEUE_H

#include "mky_libdef.h"

typedef struct mky_deque mky_queue;

mky_queue* mky_queue_create(size_t elem_size);
mky_queue* mky_queue_clone(const mky_queue *q);
void mky_queue_destroy(mky_queue *q);

void* mky_queue_push(mky_queue *q, const void *elem);
void mky_queue_pop(mky_queue *q);
void* mky_queue_top(const mky_queue *q);
void mky_queue_clear(mky_queue *q);

int mky_queue_is_empty(const mky_queue *q);
int mky_queue_size(const mky_queue *q);

#endif
