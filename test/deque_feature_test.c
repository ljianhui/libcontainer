#include <stdio.h>
#include "c_deque.h"

void dump(void *dst, const void *src, size_t size)
{
	*(int*)dst = *(int*)src;
}

void release(void *elem)
{
	return;
}

int main()
{
	c_deque *deq = c_deque_create(dump, release, sizeof(int));
	c_deque *clone = NULL;

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		c_deque_add_first(deq, &i);
	}
	
	clone = c_deque_clone(deq);

	printf("%d\n", c_deque_size(clone));

	while (!c_deque_is_empty(clone))
	{
		printf("%d, ", *(int*)c_deque_get_first(clone));
		c_deque_remove_first(clone);
	}
	printf("\n");
	c_deque_destroy(clone);
	clone = NULL;

	for (i = 0; i < 3; ++i)
	{
		c_deque_remove_last(deq);
	}

	for (i = 0; i < 10; ++i)
	{
		c_deque_add_last(deq, &i);
		c_deque_remove_first(deq);
	}

	clone = c_deque_clone(deq);
	while (!c_deque_is_empty(clone))
	{
		printf("%d, ", *(int*)c_deque_get_last(clone));
		c_deque_remove_last(clone);
	}
	printf("\n");
	c_deque_destroy(clone);
	clone = NULL;

	printf("deq.size == %d\n", c_deque_size(deq));
	c_deque_clear(deq);
	printf("deq.size == %d\n", c_deque_size(deq));

	c_deque_destroy(deq);
	return 0;
}