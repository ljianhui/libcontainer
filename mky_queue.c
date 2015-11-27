#include "mky_queue.h"
#include "mky_deque.h"

mky_queue* mky_queue_create(size_t elem_size)
{
	return mky_deque_create(elem_size);
}

mky_queue* mky_queue_clone(const mky_queue *src)
{
	return mky_deque_clone(src);
}

void mky_queue_destroy(mky_queue *q)
{
	mky_deque_destroy(q);
}

void* mky_queue_push(mky_queue *q, const void *elem)
{
	return mky_deque_add_last(q, elem);
}

void mky_queue_pop(mky_queue *q)
{
	mky_deque_remove_first(q);
}

void* mky_queue_top(const mky_queue *q)
{
	return mky_deque_get_first(q);
}

void mky_queue_clear(mky_queue *q)
{
	mky_deque_clear(q);
}

int mky_queue_is_empty(const mky_queue *q)
{
	return mky_deque_is_empty(q);
}

int mky_queue_size(const mky_queue *q)
{
	return mky_deque_size(q);
}
