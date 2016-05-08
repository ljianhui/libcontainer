#include "c_stack.h"
#include "c_deque.h"

c_stack* c_stack_create(dump_func dump, release_func release, size_t elem_size)
{
	return c_deque_create(dump, release, elem_size);
}

c_stack* c_stack_clone(const c_stack *src)
{
	return c_deque_clone(src);
}

void c_stack_destroy(c_stack *s)
{
	c_deque_destroy(s);
}

void* c_stack_push(c_stack *s, const void *elem)
{
	return c_deque_add_last(s, elem);
}

void c_stack_pop(c_stack *s)
{
	c_deque_remove_last(s);
}

void* c_stack_top(const c_stack *s)
{
	return c_deque_get_last(s);
}

void c_stack_clear(c_stack *s)
{
	c_deque_clear(s);
}

int c_stack_is_empty(const c_stack *s)
{
	return c_deque_is_empty(s);
}

int c_stack_size(const c_stack *s)
{
	return c_deque_size(s);
}
