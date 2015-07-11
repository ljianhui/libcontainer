#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

struct array
{
	char *elems;
	compare_func comparator;
	size_t elem_size;
	int size;
	int capacity;
};

struct array_iterator
{
	struct array *a;
	int cur_index;
};

static int reserve(array *a, int capacity)
{
	if (a == NULL || capacity <= a->size)
	{
		return 0;
	}

	int total_bytes = a->elem_size * capacity;
	char *new_ptr = (char*)malloc(total_bytes);
	if (new_ptr == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return 0;
	}

	if (a->elems != NULL)
	{
		memcpy(new_ptr, a->elems, a->elem_size * a->size);
		free(a->elems);
	}
	a->elems = new_ptr;
	a->capacity = capacity;
	return 1;
}

static void left_move(array *a, int start)
{
	/*
	const char *src = a->elems + start * a->elem_size;
	char *dst = a->elems + (start - 1) * a->elem_size;
	memcpy(dst, src, (a->size - start) * a->elem_size);
	*/
	const char *src = a->elems + start * a->elem_size;
	char *dst = a->elems + (start - 1) * a->elem_size;
	const char *end = a->elems + (a->size - 1) * a->elem_size;
	while (src <= end)
	{
		*dst = *src;
		++dst;
		++src;
	}
}

static void right_move(array *a, int start)
{
	/*
	const char *src = a->elems + start * a->elem_size;
	char *dst = a->elems + (start + 1) * a->elem_size;
	memcpy(dst, src, (a->size - start) * a->elem_size);
	*/
	const char *src = a->elems + (a->size - 1) * a->elem_size;
	char *dst = a->elems + a->size * a->elem_size;
	const char *end = a->elems + start * a->elem_size;
	while (src >= end)
	{
		*dst = *src;
		--src;
		--dst;
	}
}

array* create_array(size_t elem_size, compare_func comparator)
{
	return create_capacity_array(elem_size, 0, comparator);
}

array* create_capacity_array(
	size_t elem_size, int capacity, compare_func comparator)
{
	array *a = (array*)malloc(sizeof(array));
	if (a == NULL)
	{
		return NULL;
	}

	a->elems = NULL;
	a->comparator = comparator;
	a->elem_size = elem_size;
	a->size = 0;
	a->capacity = capacity;

	int total_bytes = elem_size * capacity;
	if (total_bytes >= 0)
	{
		a->elems = (char*)malloc(total_bytes);
		if (a->elems == NULL)
		{
			free(a);
			return NULL;
		}
	}
	return a;
}

array* clone_array(const array *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	array *a = create_capacity_array(
		src->elem_size, src->capacity, src->comparator);
	if (a == NULL)
	{
		return NULL;
	}

	memcpy(a->elems, src->elems, src->elem_size * src->size);
	a->size = src->size;
	return a;
}

void clear_array(array *a)
{
	if (a)
	{
		a->size = 0;
	}
}

void destroy_array(array *a)
{
	if (a == NULL)
	{
		return;
	}

	if (a->elems)
	{
		free(a->elems);
	}
	free(a);
}

int append_to_array(array *a, const void *elem)
{
	return add_to_array(a, elem, a->size);
}

int remove_last_from_array(array *a)
{
	return remove_from_array(a, a->size-1);
}

int add_to_array(array *a, const void *elem, int index)
{
	if (a == NULL || index < 0 || index > a->size)
	{
		return 0;
	}

	if (a->size == a->capacity)
	{
		int new_capacity = 1 + a->capacity + (a->capacity >> 1);
		if (!reserve(a, new_capacity))
		{
			return 0;
		}
	}

	right_move(a, index);
	memcpy(a->elems + a->elem_size * index, elem, a->elem_size);
	++a->size;
	return 1;
}

int add_all_to_array(array *dst, const array *src)
{
	if (dst == NULL || src == NULL)
	{
		return 0;
	}
	
	int total_size = dst->size + src->size;
	if (dst->capacity < total_size)
	{
		total_size += total_size >> 1;
		if (!reserve(dst, total_size))
		{
			return 0;
		}
	}
	
	memcpy(dst->elems + dst->elem_size * dst->size,
		src->elems, src->elem_size * src->size);
	dst->size += src->size;
	return 1;
}

int remove_elem_from_array(array *a, const void *elem)
{
	if (a == NULL)
	{
		return 0;
	}
	return remove_from_array(a, index_of_array(a, elem));
}

int remove_from_array(array *a, int index)
{
	if (a == NULL || index < 0 || index >= a->size)
	{
		return 0;
	}

	left_move(a, index + 1);
	--a->size;
	return 1;
}

void* get_from_array(const array *a, int index)
{
	if (a == NULL || index < 0 || index >= a->size)
	{
		return NULL;
	}
	return a->elems + a->elem_size * index;
}

int set_to_array(array *a, const void *elem, int index)
{
	if (a == NULL || index < 0 || index >= a->size)
	{
		return 0;
	}
	memcpy(a->elems + a->elem_size * index, elem, a->elem_size);
	return 1;
}

int index_of_array(const array *a, const void *elem)
{
	if (a == NULL || elem == NULL)
	{
		return -1;
	}

	int i = 0;
	char *cur_elem = a->elems;
	if (a->comparator != NULL)
	{
		for (i = 0; i < a->size; ++i)
		{
			if (a->comparator((const void*)cur_elem, elem) == 0)
			{
				return i;
			}
			cur_elem += a->elem_size;
		}
	}
	else
	{
		for (i = 0; i < a->size; ++i)
		{
			if (memcmp(cur_elem, elem, a->elem_size) == 0)
			{
				return i;
			}
			cur_elem += a->elem_size;
		}
	}
	return -1;
}

void foreach_in_array(
	array *a, visit_func vistor, void *extra_data)
{
	if (a == NULL || vistor == NULL)
	{
		return;
	}

	int i = 0;
	char *cur_elem = a->elems;
	for (i = 0; i < a->size; ++i)
	{
		if (vistor((void*)cur_elem, extra_data))
		{
			break;
		}
		cur_elem += a->elem_size;
	}
}

int is_empty_array(const array *a)
{
	if (a == NULL)
	{
		return 1;
	}
	return !a->size;
}

int size_of_array(const array *a)
{
	if (a == NULL)
	{
		return -1;
	}
	return a->size;
}

int capacity_of_array(const array *a)
{
	if (a == NULL)
	{
		return -1;
	}
	return a->capacity;
}

array_iterator* create_array_iterator(array *a)
{
	if (a == NULL)
	{
		return NULL;
	}

	array_iterator *it = (array_iterator*)
		malloc(sizeof(array_iterator));
	if (it == NULL)
	{
		return NULL;
	}

	it->a = a;
	it->cur_index = -1;
}

void destroy_array_iterator(array_iterator *it)
{
	if (it)
	{
		free(it);
	}
}

void* next_array_iterator(array_iterator *it)
{
	++it->cur_index;
	return get_from_array(it->a, it->cur_index);
}

int has_next_array_iterator(const array_iterator *it)
{
	if (it == NULL)
	{
		return 0;
	}
	return it->cur_index < it->a->size - 1;
}

void remove_by_array_iterator(array_iterator *it)
{
	if (it != NULL && it->cur_index != -1)
	{
		remove_from_array(it->a, it->cur_index);
		--it->cur_index;
	}
}

