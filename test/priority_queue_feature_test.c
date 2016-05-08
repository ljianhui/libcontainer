#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "c_priority_queue.h"

void dump(void *dst, const void *src, size_t size)
{
	*(int*)dst = *(int*)src;
}

void release(void *elem)
{
	return;
}

int comparator(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int main()
{
	c_priority_queue *queue = c_priority_queue_create(dump, release, comparator, sizeof(int));
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
		c_priority_queue_push(queue, &ret);
	}

	c_priority_queue *clone = c_priority_queue_clone(queue);
	c_priority_queue *clone2 = c_priority_queue_clone(queue);

	printf("\nsize : %d\n", c_priority_queue_size(queue));
	while (!c_priority_queue_is_empty(queue))
	{
		printf("%d, ", *(int*)c_priority_queue_top(queue));
		c_priority_queue_pop(queue);
	}
	printf("\n");

	printf("\nsize : %d\n", c_priority_queue_size(clone));
	while (!c_priority_queue_is_empty(clone))
	{
		printf("%d, ", *(int*)c_priority_queue_top(clone));
		c_priority_queue_pop(clone);
	}
	printf("\n");

	c_priority_queue_clear(clone2);
	printf("%d\n", c_priority_queue_size(clone2));

	c_priority_queue_destroy(clone);
	c_priority_queue_destroy(queue);

	return 0;
}