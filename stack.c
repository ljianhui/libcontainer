#include "stack.h"
#include "deque.h"

stack* stack_create(size_t elem_size)
{
	return deque_create(elem_size);
}

stack* stack_clone(const stack *src)
{
	return deque_clone(src);
}

void stack_destroy(stack *s)
{
	deque_destroy(s);
}

void* stack_push(stack *s, const void *elem)
{
	return deque_add_last(s, elem);
}

void stack_pop(stack *s)
{
	deque_remove_last(s);
}

void* stack_top(const stack *s)
{
	return deque_get_last(s);
}

void stack_clear(stack *s)
{
	deque_clear(s);
}

int stack_is_empty(const stack *s)
{
	return deque_is_empty(s);
}

int stack_size(const stack *s)
{
	return deque_size(s);
}
