#include <stdio.h>
#include "c_array.h"

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
	c_array *a = c_array_create(sizeof(int), comparator);
	if (a == NULL)
	{
		fprintf(stderr, "create_array failed\n");
	}

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		c_array_add_last(a, &i);
	}
	c_array_iter iter;
	c_array_iter_init(a, &iter);
	if (!c_array_iter_has_next(&iter))
	{
		fprintf(stderr, "iter failed\n");
	}
	while(c_array_iter_has_next(&iter))
	{
		printf("%d, ", *(int*)c_array_iter_next(&iter));
	}
	printf("\n");

	for (i = 0; i < 10; ++i)
	{
		c_array_add(a, &(i), i);
	}
	c_array_iter_init(a, &iter);
	while(c_array_iter_has_next(&iter))
	{
		printf("%d, ", *(int*)c_array_iter_next(&iter));
	}
	printf("\n");

	for (i = 9; i >= 0; --i)
	{
		c_array_remove(a, i);
	}
	int value = 9;
	c_array_remove_elem(a, &value);
	value = 0;
	c_array_remove_elem(a, &value);
	c_array_remove_elem(a, &value);
	c_array_foreach(a, visitor, NULL);
	printf("\n");

	printf("size: %d, capacity: %d\n", c_array_size(a), c_array_capacity(a));

	value = 10;
	c_array_set(a, &value, 0);
	value = 11;
	c_array_set(a, &value, 1);
	printf("%d, %d\n", *(int*)c_array_get(a, 0), *(int*)c_array_get(a, 1));
	
	printf("index of %d: %d\n", value, c_array_index_of(a, &value));

	c_array *new_a = c_array_clone(a);
	printf("capacity: %d\n", c_array_capacity(new_a));
	c_array_foreach(new_a, visitor, NULL);
	printf("\n");

	c_array_add_all(new_a, a);
	c_array_foreach(new_a, visitor, NULL);
	printf("\n");

	printf("isEmpty: %d\n", c_array_is_empty(new_a));
	c_array_clear(new_a);
	printf("isEmpty: %d\n", c_array_is_empty(new_a));

	value = 12;
	c_array_add_last(new_a, &value);
	value = 13;
	c_array_add_last(new_a, &value);
	c_array_foreach(new_a, visitor, NULL);
	printf("\n");

	c_array_iter_init(a, &iter);
	while (c_array_iter_has_next(&iter))
	{
		int *value = (int*)c_array_iter_next(&iter);
		if (*value == 10 || *value == 6)
			c_array_iter_remove(&iter);
	}
	c_array_foreach(a, visitor, NULL);
	printf("\n");

	c_array_destroy(new_a);
	c_array_destroy(a);
	return 0;
}
