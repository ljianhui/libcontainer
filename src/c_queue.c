#include "c_queue.h"
#include "c_deque.h"

c_queue* c_queue_create(size_t elem_size)
{
	return c_deque_create(elem_size);
}

c_queue* c_queue_clone(const c_queue *src)
{
	return c_deque_clone(src);
}

void c_queue_destroy(c_queue *q)
{
	c_deque_destroy(q);
}

void* c_queue_push(c_queue *q, const void *elem)
{
	return c_deque_add_last(q, elem);
}

void c_queue_pop(c_queue *q)
{
	c_deque_remove_first(q);
}

void* c_queue_top(const c_queue *q)
{
	return c_deque_get_first(q);
}

void c_queue_clear(c_queue *q)
{
	c_deque_clear(q);
}

int c_queue_is_empty(const c_queue *q)
{
	return c_deque_is_empty(q);
}

int c_queue_size(const c_queue *q)
{
	return c_deque_size(q);
}
