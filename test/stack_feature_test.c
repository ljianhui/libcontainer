#include <stdio.h>
#include "mky_stack.h"

int main()
{
	int i = 0;
	mky_stack *stk = mky_stack_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		mky_stack_push(stk, &i);
	}

	printf("mky_stack.size == %d\n", mky_stack_size(stk));

	for (i = 0; i < 5; ++i)
	{
		mky_stack_pop(stk);
	}

	for (i = 10; i < 15; ++i)
	{
		mky_stack_push(stk, &i);
	}

	mky_stack *clone = mky_stack_clone(stk);
	while (!mky_stack_is_empty(clone))
	{
		printf("%d, ", *(int*)mky_stack_top(clone));
		mky_stack_pop(clone);
	}
	mky_stack_destroy(clone);
	printf("\n");


	mky_stack_clear(stk);
	for (i = 0; i < 5; ++i)
	{
		mky_stack_push(stk, &i);
	}
	while (!mky_stack_is_empty(stk))
	{
		printf("%d, ", *(int*)mky_stack_top(stk));
		mky_stack_pop(stk);
	}
	printf("\n");

	mky_stack_destroy(stk);
	return 0;
}
