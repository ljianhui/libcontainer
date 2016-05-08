#ifndef _C_PRIORITY_QUEUE_H
#define _C_PRIORITY_QUEUE_H

#include "c_libdef.h"

typedef struct c_priority_queue c_priority_queue;

c_priority_queue* c_priority_queue_create(dump_func dump, release_func, compare_func compare, size_t elem_size);
c_priority_queue* c_priority_queue_clone(const c_priority_queue *src);
void c_priority_queue_destroy(c_priority_queue *pri_queue);

const void* c_priority_queue_push(c_priority_queue *pri_queue, const void *elem);
void c_priority_queue_pop(c_priority_queue *pri_queue);
void c_priority_queue_clear(c_priority_queue *pri_queue);

const void* c_priority_queue_top(c_priority_queue *pri_queue);
int c_priority_queue_size(c_priority_queue *pri_queue);
int c_priority_queue_is_empty(c_priority_queue *pri_queue);

#endif
