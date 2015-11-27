#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mky_priority_queue.h"

int comparator(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int main()
{
	mky_priority_queue *queue = mky_priority_queue_create(sizeof(int), comparator);
	if (queue == NULL)
	{
		printf("create priority queue failed\n");
	}

	srand(time(NULL));

	int ret = 0;
	int i = 0;
	for (i = 0; i < 20; ++i)
	{
		ret = rand() % 100;
		printf("%d, ", ret);
		mky_priority_queue_push(queue, &ret);
	}

	mky_priority_queue *clone = mky_priority_queue_clone(queue);
	mky_priority_queue *clone2 = mky_priority_queue_clone(queue);

	printf("\nsize : %d\n", mky_priority_queue_size(queue));
	while (!mky_priority_queue_is_empty(queue))
	{
		printf("%d, ", *(int*)mky_priority_queue_top(queue));
		mky_priority_queue_pop(queue);
	}
	printf("\n");

	printf("\nsize : %d\n", mky_priority_queue_size(clone));
	while (!mky_priority_queue_is_empty(clone))
	{
		printf("%d, ", *(int*)mky_priority_queue_top(clone));
		mky_priority_queue_pop(clone);
	}
	printf("\n");

	mky_priority_queue_clear(clone2);
	printf("%d\n", mky_priority_queue_size(clone2));

	mky_priority_queue_destroy(clone);
	mky_priority_queue_destroy(queue);

	return 0;
}