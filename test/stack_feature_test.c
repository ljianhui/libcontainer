#include <stdio.h>
#include "stack.h"

int main()
{
	int i = 0;
	stack *que = stack_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		stack_push(que, &i);
	}

	printf("stack.size == %d\n", stack_size(que));

	for (i = 0; i < 5; ++i)
	{
		stack_pop(que);
	}

	for (i = 10; i < 15; ++i)
	{
		stack_push(que, &i);
	}

	stack *clone = stack_clone(que);
	while (!stack_is_empty(clone))
	{
		printf("%d, ", *(int*)stack_top(clone));
		stack_pop(clone);
	}
	stack_destroy(clone);
	printf("\n");


	stack_clear(que);
	for (i = 0; i < 5; ++i)
	{
		stack_push(que, &i);
	}
	while (!stack_is_empty(que))
	{
		printf("%d, ", *(int*)stack_top(que));
		stack_pop(que);
	}
	printf("\n");

	stack_destroy(que);
	return 0;
}
