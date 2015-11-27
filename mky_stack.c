#include "mky_stack.h"
#include "mky_deque.h"

mky_stack* mky_stack_create(size_t elem_size)
{
	return mky_deque_create(elem_size);
}

mky_stack* mky_stack_clone(const mky_stack *src)
{
	return mky_deque_clone(src);
}

void mky_stack_destroy(mky_stack *s)
{
	mky_deque_destroy(s);
}

void* mky_stack_push(mky_stack *s, const void *elem)
{
	return mky_deque_add_last(s, elem);
}

void mky_stack_pop(mky_stack *s)
{
	mky_deque_remove_last(s);
}

void* mky_stack_top(const mky_stack *s)
{
	return mky_deque_get_last(s);
}

void mky_stack_clear(mky_stack *s)
{
	mky_deque_clear(s);
}

int mky_stack_is_empty(const mky_stack *s)
{
	return mky_deque_is_empty(s);
}

int mky_stack_size(const mky_stack *s)
{
	return mky_deque_size(s);
}
