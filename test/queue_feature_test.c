#include <stdio.h>
#include "mky_queue.h"

int main()
{
	int i = 0;
	mky_queue *que = mky_queue_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		mky_queue_push(que, &i);
	}

	printf("mky_queue.size == %d\n", mky_queue_size(que));

	for (i = 0; i < 5; ++i)
	{
		mky_queue_pop(que);
	}

	for (i = 10; i < 15; ++i)
	{
		mky_queue_push(que, &i);
	}

	mky_queue *clone = mky_queue_clone(que);
	while (!mky_queue_is_empty(clone))
	{
		printf("%d, ", *(int*)mky_queue_top(clone));
		mky_queue_pop(clone);
	}
	mky_queue_destroy(clone);
	printf("\n");


	mky_queue_clear(que);
	for (i = 0; i < 5; ++i)
	{
		mky_queue_push(que, &i);
	}
	while (!mky_queue_is_empty(que))
	{
		printf("%d, ", *(int*)mky_queue_top(que));
		mky_queue_pop(que);
	}
	printf("\n");

	mky_queue_destroy(que);
	return 0;
}
