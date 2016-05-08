#include <stdio.h>
#include "c_list.h"

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

int visitor(void *element, void *extra)
{
	printf("%d, ", *(int*)element);
	return 0;
}

int main()
{
	int i = 0;
	c_list *lst = c_list_create(dump, release,  comparator, sizeof(int));
	if (lst == NULL)
	{
		fprintf(stderr, "create c_list failed\n");
	}

	for (i = 0; i < 10; ++i)
	{
		c_list_add_first(lst, &i);
	}
	c_list_foreach(lst, visitor, NULL); // 1
	printf("\n");

	c_list_clear(lst);
	for (i = 0; i < 10; ++i)
	{
		c_list_add_last(lst, &i);
	}
	c_list_foreach(lst, visitor, NULL);	// 2
	printf("size: %d\n", c_list_size(lst));

	i = 100;
	c_list_add(lst, &i, 0);
	c_list_add(lst, &i, c_list_size(lst));
	c_list_add(lst, &i, c_list_size(lst) / 2);

	c_list_iter it;
	c_list_iter_init(lst, &it);
	while (c_list_iter_has_next(&it))
	{
		printf("%d, ", *(int*)c_list_iter_next(&it));
	}
	printf("size: %d\n", c_list_size(lst)); // 3

	c_list *clone = c_list_clone(lst);
	c_list_foreach(clone, visitor, NULL);	// 4
	printf("size: %d\n", c_list_size(clone));

	c_list_add_all(lst, clone);
	c_list_foreach(lst, visitor, NULL); // 5
	printf("size: %d\n", c_list_size(lst));

	i = 8;
	c_list_remove_first(lst);
	c_list_remove_last(lst);
	c_list_remove_elem(lst, &i);
	c_list_remove(lst, 2);
	c_list_foreach(lst, visitor, NULL);	// 6
	printf("size: %d\n", c_list_size(lst));

	printf("first: %d, last: %d, index 10: %d\n",
		*(int*)c_list_get_first(lst), *(int*)c_list_get_last(lst), *(int*)c_list_get(lst, 10));	// 7

	i = 102;
	c_list_set_first(lst, &i);
	c_list_set_last(lst, &i);
	c_list_set(lst, &i, 20);
	c_list_foreach(lst, visitor, NULL); // 8
	printf("size: %d\n", c_list_size(lst));

	i = 9;
	c_list_find(lst, &i, &it);
	if (c_list_iter_elem(&it)) // 9
	{
		printf("find success: %d\n", *(int*)c_list_iter_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}
	i = 111;
	c_list_find(lst, &i, &it);
	if (c_list_iter_elem(&it)) // 10
	{
		printf("find success: %d\n", *(int*)c_list_iter_elem(&it));
	}
	else
	{
		printf("find failed\n");
	}

	printf("%s\n", c_list_is_empty(lst)? "lst is empty" : "lst is not empty");	// 11

	c_list_iter_init(lst, &it);
	int elem = 0;
	while (c_list_iter_has_next(&it))
	{
		elem = *(int*)c_list_iter_next(&it);
		if (elem == 100)
		{
			c_list_iter_remove(&it);
		}
		else
		{
			printf("%d, ", elem);
		}
	}
	printf("size: %d\n", c_list_size(lst));

	c_list_iter_init(lst, &it);
	int new_elem = 123;
	while (c_list_iter_has_next(&it))
	{
		elem = *(int*)c_list_iter_next(&it);
		printf("%d, ", elem);
		if (elem == 5)
		{
			c_list_iter_add(&it, &new_elem);
			printf("%d, ", *(int*)c_list_iter_elem(&it));
			c_list_iter_next(&it);
		}
	}
	printf("size: %d\n", c_list_size(lst));

	c_list_foreach(lst, visitor, NULL);
	printf("size: %d\n", c_list_size(lst));

	c_list_destroy(clone);
	c_list_destroy(lst);
	return 0;
}

