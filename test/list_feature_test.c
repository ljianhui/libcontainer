#include <stdio.h>
#include "mky_list.h"

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
	mky_list *lst = mky_list_create(sizeof(int), comparator);
	if (lst == NULL)
	{
		fprintf(stderr, "create mky_list failed\n");
	}

	for (i = 0; i < 10; ++i)
	{
		mky_list_add_first(lst, &i);
	}
	mky_list_foreach(lst, visitor, NULL); // 1
	printf("\n");

	mky_list_clear(lst);
	for (i = 0; i < 10; ++i)
	{
		mky_list_add_last(lst, &i);
	}
	mky_list_foreach(lst, visitor, NULL);	// 2
	printf("size: %d\n", mky_list_size(lst));

	i = 100;
	mky_list_add(lst, &i, 0);
	mky_list_add(lst, &i, mky_list_size(lst));
	mky_list_add(lst, &i, mky_list_size(lst) / 2);

	mky_list_iter it;
	mky_list_iter_init(lst, &it);
	while (mky_list_iter_has_next(&it))
	{
		printf("%d, ", *(int*)mky_list_iter_next(&it));
	}
	printf("size: %d\n", mky_list_size(lst)); // 3

	mky_list *clone = mky_list_clone(lst);
	mky_list_foreach(clone, visitor, NULL);	// 4
	printf("size: %d\n", mky_list_size(clone));

	mky_list_add_all(lst, clone);
	mky_list_foreach(lst, visitor, NULL); // 5
	printf("size: %d\n", mky_list_size(lst));

	i = 8;
	mky_list_remove_first(lst);
	mky_list_remove_last(lst);
	mky_list_remove_elem(lst, &i);
	mky_list_remove(lst, 2);
	mky_list_foreach(lst, visitor, NULL);	// 6
	printf("size: %d\n", mky_list_size(lst));

	printf("first: %d, last: %d, index 10: %d\n",
		*(int*)mky_list_get_first(lst), *(int*)mky_list_get_last(lst), *(int*)mky_list_get(lst, 10));	// 7

	i = 102;
	mky_list_set_first(lst, &i);
	mky_list_set_last(lst, &i);
	mky_list_set(lst, &i, 20);
	mky_list_foreach(lst, visitor, NULL); // 8
	printf("size: %d\n", mky_list_size(lst));

	i = 9;
	if (mky_list_find(lst, &i, &it)) // 9
	{
		printf("find success: %d\n", *(int*)mky_list_iter_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}
	i = 111;
	if (mky_list_find(lst, &i, &it)) // 10
	{
		printf("find success: %d\n", *(int*)mky_list_iter_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}

	printf("%s\n", mky_list_is_empty(lst)? "lst is empty" : "lst is not empty");	// 11

	mky_list_iter_init(lst, &it);
	int elem = 0;
	while (mky_list_iter_has_next(&it))
	{
		elem = *(int*)mky_list_iter_next(&it);
		if (elem == 100)
		{
			mky_list_iter_remove(&it);
		}
		else
		{
			printf("%d, ", elem);
		}
	}
	printf("size: %d\n", mky_list_size(lst));

	mky_list_iter_init(lst, &it);
	int new_elem = 123;
	while (mky_list_iter_has_next(&it))
	{
		elem = *(int*)mky_list_iter_next(&it);
		printf("%d, ", elem);
		if (elem == 5)
		{
			mky_list_iter_add(&it, &new_elem);
			printf("%d, ", *(int*)mky_list_iter_elem(&it));
			mky_list_iter_next(&it);
		}
	}
	printf("size: %d\n", mky_list_size(lst));

	mky_list_foreach(lst, visitor, NULL);
	printf("size: %d\n", mky_list_size(lst));

	mky_list_destroy(clone);
	mky_list_destroy(lst);
	return 0;
}

