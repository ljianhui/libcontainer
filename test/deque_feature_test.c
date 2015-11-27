#include <stdio.h>
#include "mky_deque.h"

int main()
{
	mky_deque *deq = mky_deque_create(sizeof(int));
	mky_deque *clone = NULL;

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		mky_deque_add_first(deq, &i);
	}
	
	clone = mky_deque_clone(deq);

	printf("%d\n", mky_deque_size(clone));

	while (!mky_deque_is_empty(clone))
	{
		printf("%d, ", *(int*)mky_deque_get_first(clone));
		mky_deque_remove_first(clone);
	}
	printf("\n");
	mky_deque_destroy(clone);
	clone = NULL;

	for (i = 0; i < 3; ++i)
	{
		mky_deque_remove_last(deq);
	}

	for (i = 0; i < 10; ++i)
	{
		mky_deque_add_last(deq, &i);
		mky_deque_remove_first(deq);
	}

	clone = mky_deque_clone(deq);
	while (!mky_deque_is_empty(clone))
	{
		printf("%d, ", *(int*)mky_deque_get_last(clone));
		mky_deque_remove_last(clone);
	}
	printf("\n");
	mky_deque_destroy(clone);
	clone = NULL;

	printf("deq.size == %d\n", mky_deque_size(deq));
	mky_deque_clear(deq);
	printf("deq.size == %d\n", mky_deque_size(deq));

	mky_deque_destroy(deq);
	return 0;
}