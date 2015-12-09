#include <stdio.h>
#include "c_queue.h"

int main()
{
	int i = 0;
	c_queue *que = c_queue_create(sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		c_queue_push(que, &i);
	}

	printf("c_queue.size == %d\n", c_queue_size(que));

	for (i = 0; i < 5; ++i)
	{
		c_queue_pop(que);
	}

	for (i = 10; i < 15; ++i)
	{
		c_queue_push(que, &i);
	}

	c_queue *clone = c_queue_clone(que);
	while (!c_queue_is_empty(clone))
	{
		printf("%d, ", *(int*)c_queue_top(clone));
		c_queue_pop(clone);
	}
	c_queue_destroy(clone);
	printf("\n");


	c_queue_clear(que);
	for (i = 0; i < 5; ++i)
	{
		c_queue_push(que, &i);
	}
	while (!c_queue_is_empty(que))
	{
		printf("%d, ", *(int*)c_queue_top(que));
		c_queue_pop(que);
	}
	printf("\n");

	c_queue_destroy(que);
	return 0;
}
