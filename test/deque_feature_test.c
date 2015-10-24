#include <stdio.h>
#include "deque.h"

int main()
{
	deque *deq = deque_create(sizeof(int));
	deque *clone = NULL;

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		deque_add_first(deq, &i);
	}
	
	clone = deque_clone(deq);

	printf("%d\n", deque_size(clone));

	while (!deque_is_empty(clone))
	{
		printf("%d, ", *(int*)deque_get_first(clone));
		deque_remove_first(clone);
	}
	printf("\n");
	deque_destroy(clone);
	clone = NULL;

	for (i = 0; i < 3; ++i)
	{
		deque_remove_last(deq);
	}

	for (i = 0; i < 10; ++i)
	{
		deque_add_last(deq, &i);
		deque_remove_first(deq);
	}

	clone = deque_clone(deq);
	while (!deque_is_empty(clone))
	{
		printf("%d, ", *(int*)deque_get_last(clone));
		deque_remove_last(clone);
	}
	printf("\n");
	deque_destroy(clone);
	clone = NULL;

	printf("deq.size == %d\n", deque_size(deq));
	deque_clear(deq);
	printf("deq.size == %d\n", deque_size(deq));

	deque_destroy(deq);
	return 0;
}