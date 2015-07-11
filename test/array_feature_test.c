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
	array *a = create_array(sizeof(int), comparator);
	if (a == NULL)
	{
		printf("create_array failed\n");
	}

	int i = 0;
	for (i = 0; i < 10; ++i)
	{
		append_to_array(a, &i);
	}
	array_iterator *iterator = create_array_iterator(a);
	if (!has_next_array_iterator(iterator))
	{
		printf("iterator failed\n");
	}
	while(has_next_array_iterator(iterator))
	{
		printf("%d, ", *(int*)next_array_iterator(iterator));
	}
	printf("\n");
	destroy_array_iterator(iterator);

	for (i = 0; i < 10; ++i)
	{
		add_to_array(a, &(i), i);
	}
	iterator = create_array_iterator(a);
	while(has_next_array_iterator(iterator))
	{
		printf("%d, ", *(int*)next_array_iterator(iterator));
	}
	printf("\n");
	destroy_array_iterator(iterator);

	for (i = 9; i >= 0; --i)
	{
		remove_from_array(a, i);
	}
	int value = 9;
	remove_elem_from_array(a, &value);
	value = 0;
	remove_elem_from_array(a, &value);
	remove_elem_from_array(a, &value);
	foreach_in_array(a, visitor, NULL);
	printf("\n");

	printf("size: %d, capacity: %d\n",
	        size_of_array(a), capacity_of_array(a));

	value = 10;
	set_to_array(a, &value, 0);
	value = 11;
	set_to_array(a, &value, 1);
	printf("%d, %d\n", *(int*)get_from_array(a, 0), *(int*)get_from_array(a, 1));
	
	printf("index of %d: %d\n", value, index_of_array(a, &value));

	array *new_a = clone_array(a);
	printf("capacity: %d\n", capacity_of_array(new_a));
	foreach_in_array(new_a, visitor, NULL);
	printf("\n");

	add_all_to_array(new_a, a);
	foreach_in_array(new_a, visitor, NULL);
	printf("\n");

	printf("isEmpty: %d\n", is_empty_array(new_a));
	clear_array(new_a);
	printf("isEmpty: %d\n", is_empty_array(new_a));

	value = 12;
	append_to_array(new_a, &value);
	value = 13;
	append_to_array(new_a, &value);
	foreach_in_array(new_a, visitor, NULL);
	printf("\n");

	iterator = create_array_iterator(a);
	while (has_next_array_iterator(iterator))
	{
		int *value = (int*)next_array_iterator(iterator);
		if (*value == 10 || *value == 6)
			remove_by_array_iterator(iterator);
	}
	foreach_in_array(a, visitor, NULL);
	printf("\n");
	destroy_array_iterator(iterator);

	destroy_array(new_a);
	destroy_array(a);
	return 0;
}
