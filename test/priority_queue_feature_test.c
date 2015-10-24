#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"

int comparator(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int main()
{
	priority_queue *queue = priority_queue_create(sizeof(int), comparator);
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
		priority_queue_push(queue, &ret);
	}

	priority_queue *clone = priority_queue_clone(queue);
	priority_queue *clone2 = priority_queue_clone(queue);

	printf("\nsize : %d\n", priority_queue_size(queue));
	while (!priority_queue_is_empty(queue))
	{
		printf("%d, ", *(int*)priority_queue_top(queue));
		priority_queue_pop(queue);
	}
	printf("\n");

	printf("\nsize : %d\n", priority_queue_size(clone));
	while (!priority_queue_is_empty(clone))
	{
		printf("%d, ", *(int*)priority_queue_top(clone));
		priority_queue_pop(clone);
	}
	printf("\n");

	priority_queue_clear(clone2);
	printf("%d\n", priority_queue_size(clone2));

	priority_queue_destroy(clone);
	priority_queue_destroy(queue);

	return 0;
}