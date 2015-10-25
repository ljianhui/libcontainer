#include <stdio.h>
#include "queue.h"

int main()
{
	int i = 0;
	queue *que = queue_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		queue_push(que, &i);
	}

	printf("queue.size == %d\n", queue_size(que));

	for (i = 0; i < 5; ++i)
	{
		queue_pop(que);
	}

	for (i = 10; i < 15; ++i)
	{
		queue_push(que, &i);
	}

	queue *clone = queue_clone(que);
	while (!queue_is_empty(clone))
	{
		printf("%d, ", *(int*)queue_top(clone));
		queue_pop(clone);
	}
	queue_destroy(clone);
	printf("\n");


	queue_clear(que);
	for (i = 0; i < 5; ++i)
	{
		queue_push(que, &i);
	}
	while (!queue_is_empty(que))
	{
		printf("%d, ", *(int*)queue_top(que));
		queue_pop(que);
	}
	printf("\n");

	queue_destroy(que);
	return 0;
}
