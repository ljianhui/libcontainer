#include "queue.h"
#include "deque.h"

queue* queue_create(size_t elem_size)
{
	return deque_create(elem_size);
}

queue* queue_clone(const queue *src)
{
	return deque_clone(src);
}

void queue_destroy(queue *q)
{
	deque_destroy(q);
}

void* queue_push(queue *q, const void *elem)
{
	return deque_add_last(q, elem);
}

void queue_pop(queue *q)
{
	deque_remove_first(q);
}

void* queue_top(const queue *q)
{
	return deque_get_first(q);
}

void queue_clear(queue *q)
{
	deque_clear(q);
}

int queue_is_empty(const queue *q)
{
	return deque_is_empty(q);
}

int queue_size(const queue *q)
{
	return deque_size(q);
}
