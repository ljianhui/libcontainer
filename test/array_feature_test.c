#include <stdio.h>
#include "mky_array.h"

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
	mky_array *a = mky_array_create(sizeof(int), comparator);
	if (a == NULL)
	{
		fprintf(stderr, "create_array failed\n");
	}

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		mky_array_add_last(a, &i);
	}
	mky_array_iter iter;
	mky_array_iter_init(a, &iter);
	if (!mky_array_iter_has_next(&iter))
	{
		fprintf(stderr, "iter failed\n");
	}
	while(mky_array_iter_has_next(&iter))
	{
		printf("%d, ", *(int*)mky_array_iter_next(&iter));
	}
	printf("\n");

	for (i = 0; i < 10; ++i)
	{
		mky_array_add(a, &(i), i);
	}
	mky_array_iter_init(a, &iter);
	while(mky_array_iter_has_next(&iter))
	{
		printf("%d, ", *(int*)mky_array_iter_next(&iter));
	}
	printf("\n");

	for (i = 9; i >= 0; --i)
	{
		mky_array_remove(a, i);
	}
	int value = 9;
	mky_array_remove_elem(a, &value);
	value = 0;
	mky_array_remove_elem(a, &value);
	mky_array_remove_elem(a, &value);
	mky_array_foreach(a, visitor, NULL);
	printf("\n");

	printf("size: %d, capacity: %d\n", mky_array_size(a), mky_array_capacity(a));

	value = 10;
	mky_array_set(a, &value, 0);
	value = 11;
	mky_array_set(a, &value, 1);
	printf("%d, %d\n", *(int*)mky_array_get(a, 0), *(int*)mky_array_get(a, 1));
	
	printf("index of %d: %d\n", value, mky_array_index_of(a, &value));

	mky_array *new_a = mky_array_clone(a);
	printf("capacity: %d\n", mky_array_capacity(new_a));
	mky_array_foreach(new_a, visitor, NULL);
	printf("\n");

	mky_array_add_all(new_a, a);
	mky_array_foreach(new_a, visitor, NULL);
	printf("\n");

	printf("isEmpty: %d\n", mky_array_is_empty(new_a));
	mky_array_clear(new_a);
	printf("isEmpty: %d\n", mky_array_is_empty(new_a));

	value = 12;
	mky_array_add_last(new_a, &value);
	value = 13;
	mky_array_add_last(new_a, &value);
	mky_array_foreach(new_a, visitor, NULL);
	printf("\n");

	mky_array_iter_init(a, &iter);
	while (mky_array_iter_has_next(&iter))
	{
		int *value = (int*)mky_array_iter_next(&iter);
		if (*value == 10 || *value == 6)
			mky_array_iter_remove(&iter);
	}
	mky_array_foreach(a, visitor, NULL);
	printf("\n");

	mky_array_destroy(new_a);
	mky_array_destroy(a);
	return 0;
}
