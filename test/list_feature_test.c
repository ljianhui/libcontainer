#include <stdio.h>
#include "list.h"

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
	int i = 0;
	list *lst = list_create(sizeof(int), comparator);
	if (lst == NULL)
	{
		fprintf(stderr, "create list failed\n");
	}

	for (i = 0; i < 10; ++i)
	{
		list_add_first(lst, &i);
	}
	list_foreach(lst, visitor, NULL); // 1
	printf("\n");

	list_clear(lst);
	for (i = 0; i < 10; ++i)
	{
		list_add_last(lst, &i);
	}
	list_foreach(lst, visitor, NULL);	// 2
	printf("size: %d\n", list_size(lst));

	i = 100;
	list_add(lst, &i, 0);
	list_add(lst, &i, list_size(lst));
	list_add(lst, &i, list_size(lst) / 2);

	list_iterator it;
	list_iterator_init(lst, &it);
	while (list_iterator_has_next(&it))
	{
		printf("%d, ", *(int*)list_iterator_next(&it));
	}
	printf("size: %d\n", list_size(lst)); // 3

	list *clone = list_clone(lst);
	list_foreach(clone, visitor, NULL);	// 4
	printf("size: %d\n", list_size(clone));

	list_add_all(lst, clone);
	list_foreach(lst, visitor, NULL); // 5
	printf("size: %d\n", list_size(lst));

	i = 8;
	list_remove_first(lst);
	list_remove_last(lst);
	list_remove_elem(lst, &i);
	list_remove(lst, 2);
	list_foreach(lst, visitor, NULL);	// 6
	printf("size: %d\n", list_size(lst));

	printf("first: %d, last: %d, index 10: %d\n",
		*(int*)list_get_first(lst), *(int*)list_get_last(lst), *(int*)list_get(lst, 10));	// 7

	i = 102;
	list_set_first(lst, &i);
	list_set_last(lst, &i);
	list_set(lst, &i, 20);
	list_foreach(lst, visitor, NULL); // 8
	printf("size: %d\n", list_size(lst));

	i = 9;
	if (list_find(lst, &i, &it)) // 9
	{
		printf("find success: %d\n", *(int*)list_iterator_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}
	i = 111;
	if (list_find(lst, &i, &it)) // 10
	{
		printf("find success: %d\n", *(int*)list_iterator_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}

	printf("%s\n", list_is_empty(lst)? "lst is empty" : "lst is not empty");	// 11

	list_iterator_init(lst, &it);
	int elem = 0;
	while (list_iterator_has_next(&it))
	{
		elem = *(int*)list_iterator_next(&it);
		if (elem == 100)
		{
			list_iterator_remove(&it);
		}
		else
		{
			printf("%d, ", elem);
		}
	}
	printf("size: %d\n", list_size(lst));

	list_iterator_init(lst, &it);
	int new_elem = 123;
	while (list_iterator_has_next(&it))
	{
		elem = *(int*)list_iterator_next(&it);
		printf("%d, ", elem);
		if (elem == 5)
		{
			list_iterator_add(&it, &new_elem);
			printf("%d, ", *(int*)list_iterator_elem(&it));
			list_iterator_next(&it);
		}
	}
	printf("size: %d\n", list_size(lst));

	list_foreach(lst, visitor, NULL);
	printf("size: %d\n", list_size(lst));

	list_destroy(clone);
	list_destroy(lst);
	return 0;
}

