#include <stdio.h>
#include "array.h"

int comparator(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int visitor(void *element, void *extra)
{
	printf("%d, ", *(int*)element);
	return 0;
}

int main()
{
	array *a = array_create(sizeof(int), comparator);
	if (a == NULL)
	{
		fprintf(stderr, "create_array failed\n");
	}

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		array_add_last(a, &i);
	}
	array_iterator iterator;
	array_iterator_init(a, &iterator);
	if (!array_iterator_has_next(&iterator))
	{
		fprintf(stderr, "iterator failed\n");
	}
	while(array_iterator_has_next(&iterator))
	{
		printf("%d, ", *(int*)array_iterator_next(&iterator));
	}
	printf("\n");

	for (i = 0; i < 10; ++i)
	{
		array_add(a, &(i), i);
	}
	array_iterator_init(a, &iterator);
	while(array_iterator_has_next(&iterator))
	{
		printf("%d, ", *(int*)array_iterator_next(&iterator));
	}
	printf("\n");

	for (i = 9; i >= 0; --i)
	{
		array_remove(a, i);
	}
	int value = 9;
	array_remove_elem(a, &value);
	value = 0;
	array_remove_elem(a, &value);
	array_remove_elem(a, &value);
	array_foreach(a, visitor, NULL);
	printf("\n");

	printf("size: %d, capacity: %d\n", array_size(a), array_capacity(a));

	value = 10;
	array_set(a, &value, 0);
	value = 11;
	array_set(a, &value, 1);
	printf("%d, %d\n", *(int*)array_get(a, 0), *(int*)array_get(a, 1));
	
	printf("index of %d: %d\n", value, array_index_of(a, &value));

	array *new_a = array_clone(a);
	printf("capacity: %d\n", array_capacity(new_a));
	array_foreach(new_a, visitor, NULL);
	printf("\n");

	array_add_all(new_a, a);
	array_foreach(new_a, visitor, NULL);
	printf("\n");

	printf("isEmpty: %d\n", array_is_empty(new_a));
	array_clear(new_a);
	printf("isEmpty: %d\n", array_is_empty(new_a));

	value = 12;
	array_add_last(new_a, &value);
	value = 13;
	array_add_last(new_a, &value);
	array_foreach(new_a, visitor, NULL);
	printf("\n");

	array_iterator_init(a, &iterator);
	while (array_iterator_has_next(&iterator))
	{
		int *value = (int*)array_iterator_next(&iterator);
		if (*value == 10 || *value == 6)
			array_iterator_remove(&iterator);
	}
	array_foreach(a, visitor, NULL);
	printf("\n");

	array_destroy(new_a);
	array_destroy(a);
	return 0;
}
