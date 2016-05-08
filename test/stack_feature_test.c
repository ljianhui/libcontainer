#include <stdio.h>
#include "c_stack.h"

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
	int i = 0;
	c_stack *stk = c_stack_create(dump, release, sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		c_stack_push(stk, &i);
	}

	printf("c_stack.size == %d\n", c_stack_size(stk));

	for (i = 0; i < 5; ++i)
	{
		c_stack_pop(stk);
	}

	for (i = 10; i < 15; ++i)
	{
		c_stack_push(stk, &i);
	}

	c_stack *clone = c_stack_clone(stk);
	while (!c_stack_is_empty(clone))
	{
		printf("%d, ", *(int*)c_stack_top(clone));
		c_stack_pop(clone);
	}
	c_stack_destroy(clone);
	printf("\n");


	c_stack_clear(stk);
	for (i = 0; i < 5; ++i)
	{
		c_stack_push(stk, &i);
	}
	while (!c_stack_is_empty(stk))
	{
		printf("%d, ", *(int*)c_stack_top(stk));
		c_stack_pop(stk);
	}
	printf("\n");

	c_stack_destroy(stk);
	return 0;
}
