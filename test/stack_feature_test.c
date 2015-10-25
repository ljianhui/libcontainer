#include <stdio.h>
#include "stack.h"

int main()
{
	int i = 0;
	stack *stk = stack_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		stack_push(stk, &i);
	}

	printf("stack.size == %d\n", stack_size(stk));

	for (i = 0; i < 5; ++i)
	{
		stack_pop(stk);
	}

	for (i = 10; i < 15; ++i)
	{
		stack_push(stk, &i);
	}

	stack *clone = stack_clone(stk);
	while (!stack_is_empty(clone))
	{
		printf("%d, ", *(int*)stack_top(clone));
		stack_pop(clone);
	}
	stack_destroy(clone);
	printf("\n");


	stack_clear(stk);
	for (i = 0; i < 5; ++i)
	{
		stack_push(stk, &i);
	}
	while (!stack_is_empty(stk))
	{
		printf("%d, ", *(int*)stack_top(stk));
		stack_pop(stk);
	}
	printf("\n");

	stack_destroy(stk);
	return 0;
}
