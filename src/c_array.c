#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_array.h"

struct c_array
{
	char *elems;
	compare_func comparator;
	size_t elem_size;
	int size;
	int capacity;
};

static int c_array_reserve(c_array *a, int capacity)
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

static void c_array_left_move(c_array *a, int start)
{
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

static void c_array_right_move(c_array *a, int start)
{
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

c_array* c_array_create(size_t elem_size, compare_func comparator)
{
	return c_array_create_capacity(elem_size, 0, comparator);
}

c_array* c_array_create_capacity(
	size_t elem_size, int capacity, compare_func comparator)
{
	c_array *a = (c_array*)malloc(sizeof(c_array));
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

c_array* c_array_clone(const c_array *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	c_array *a = c_array_create_capacity(
		src->elem_size, src->capacity, src->comparator);
	if (a == NULL)
	{
		return NULL;
	}

	memcpy(a->elems, src->elems, src->elem_size * src->size);
	a->size = src->size;
	return a;
}

void c_array_clear(c_array *a)
{
	if (a)
	{
		a->size = 0;
	}
}

void c_array_destroy(c_array *a)
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

void* c_array_add_last(c_array *a, const void *elem)
{
	return c_array_add(a, elem, a->size);
}

int c_array_remove_last(c_array *a)
{
	return c_array_remove(a, a->size-1);
}

void* c_array_add(c_array *a, const void *elem, int index)
{
	if (a == NULL || elem == NULL || index < 0 || index > a->size)
	{
		return NULL;
	}

	if (a->size == a->capacity)
	{
		int new_capacity = 1 + a->capacity + (a->capacity >> 1);
		if (!c_array_reserve(a, new_capacity))
		{
			return NULL;
		}
	}

	c_array_right_move(a, index);
	char *dst = a->elems + a->elem_size * index;
	if (elem != C_ELEM_ZERO)
	{
		memcpy(dst, elem, a->elem_size);	
	}
	else
	{
		memset(dst, 0, a->elem_size);
	}
	++a->size;
	return dst;
}

int c_array_add_all(c_array *dst, const c_array *src)
{
	if (dst == NULL || src == NULL)
	{
		return 0;
	}
	
	int total_size = dst->size + src->size;
	if (dst->capacity < total_size)
	{
		total_size += total_size >> 1;
		if (!c_array_reserve(dst, total_size))
		{
			return 0;
		}
	}
	
	memcpy(dst->elems + dst->elem_size * dst->size,
		src->elems, src->elem_size * src->size);
	dst->size += src->size;
	return 1;
}

int c_array_remove_elem(c_array *a, const void *elem)
{
	if (a == NULL)
	{
		return 0;
	}
	return c_array_remove(a, c_array_index_of(a, elem));
}

int c_array_remove(c_array *a, int index)
{
	if (a == NULL || index < 0 || index >= a->size)
	{
		return 0;
	}

	c_array_left_move(a, index + 1);
	--a->size;
	return 1;
}

void* c_array_get(const c_array *a, int index)
{
	if (a == NULL || index < 0 || index >= a->size)
	{
		return NULL;
	}
	return a->elems + a->elem_size * index;
}

int c_array_set(c_array *a, const void *elem, int index)
{
	if (a == NULL || elem == NULL ||
		index < 0 || index >= a->size)
	{
		return 0;
	}
	
	if (elem != C_ELEM_ZERO)
	{
		memcpy(a->elems + a->elem_size * index, elem, a->elem_size);
	}
	else
	{
		memset(a->elems + a->elem_size * index, 0, a->elem_size);
	}
	
	return 1;
}

int c_array_index_of(const c_array *a, const void *elem)
{
	if (a == NULL || elem == NULL || a->comparator == NULL)
	{
		return -1;
	}

	int i = 0;
	char *cur_elem = a->elems;
	for (i = 0; i < a->size; ++i)
	{
		if (a->comparator((const void*)cur_elem, elem) == 0)
		{
			return i;
		}
		cur_elem += a->elem_size;
	}
	return -1;
}

void c_array_foreach(
	c_array *a, visit_func vistor, void *extra_data)
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

int c_array_is_empty(const c_array *a)
{
	if (a == NULL)
	{
		return 1;
	}
	return !a->size;
}

int c_array_size(const c_array *a)
{
	if (a == NULL)
	{
		return -1;
	}
	return a->size;
}

int c_array_capacity(const c_array *a)
{
	if (a == NULL)
	{
		return -1;
	}
	return a->capacity;
}

int c_array_iter_init(c_array *a, c_array_iter *it)
{
	if (it == NULL)
	{
		return 0;
	}

	it->a = a;
	it->cur_index = -1;
	return 1;
}

void* c_array_iter_next(c_array_iter *it)
{
	if (!c_array_iter_has_next(it))
	{
		return NULL;
	}

	++it->cur_index;
	return c_array_get(it->a, it->cur_index);
}

void* c_array_iter_elem(c_array_iter *it)
{
	if (it == NULL || it->a == NULL)
	{
		return NULL;
	}

	return c_array_get(it->a, it->cur_index);
}

int c_array_iter_has_next(const c_array_iter *it)
{
	if (it == NULL || it->a == NULL)
	{
		return 0;
	}
	return it->cur_index < it->a->size - 1;
}

void c_array_iter_remove(c_array_iter *it)
{
	if (it != NULL && it->a != NULL && it->cur_index >= 0)
	{
		c_array_remove(it->a, it->cur_index);
		--it->cur_index;
	}
}
