#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "c_priority_queue.h"

// The index of elems begin from 1, not 0

#define MIN_PRI_QUEUE_SIZE 16

typedef void* elem_type;

struct c_priority_queue
{
	elem_type *elems;
	size_t elem_size;
	int size;
	int capacity;
	c_elem_opt opt;
};

static int c_priority_queue_reserve(c_priority_queue *pri_queue)
{
	int new_capacity = pri_queue->capacity + (pri_queue->capacity >> 1);

	elem_type *elems = (elem_type*)malloc(sizeof(elem_type) * (new_capacity+1));
	if (elems == NULL)
	{
		return 0;
	}

	memset(elems, 0, sizeof(elem_type) * (new_capacity+1));
	memcpy(elems, pri_queue->elems, sizeof(elem_type) * (pri_queue->capacity+1));

	free(pri_queue->elems);
	pri_queue->elems = elems;
	pri_queue->capacity = new_capacity;
	return 1;
}

static c_priority_queue* c_priority_queue_create_capacity(dump_func dump, release_func release, compare_func compare, size_t elem_size, int capacity)
{
	if (dump == NULL || release == NULL || compare == NULL || elem_size == 0 || capacity <= 0)
	{
		return NULL;
	}

	c_priority_queue *pri_queue = (c_priority_queue*)malloc(sizeof(c_priority_queue));
	if (pri_queue == NULL)
	{
		return NULL;
	}

	pri_queue->elems = (elem_type*)malloc(sizeof(elem_type) * (capacity + 1));
	if (pri_queue->elems == NULL)
	{
		free(pri_queue);
		return NULL;
	}

	memset(pri_queue->elems, 0, sizeof(elem_type) * (capacity + 1));
	pri_queue->elem_size = elem_size;
	pri_queue->size = 0;
	pri_queue->capacity = capacity;
	pri_queue->opt.dump = dump;
	pri_queue->opt.release = release;
	pri_queue->opt.compare = compare;
	return pri_queue;
}

c_priority_queue* c_priority_queue_create(dump_func dump, release_func release, compare_func compare, size_t elem_size)
{
	return c_priority_queue_create_capacity(dump, release, compare, elem_size, MIN_PRI_QUEUE_SIZE);
}

c_priority_queue* c_priority_queue_clone(const c_priority_queue *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	c_priority_queue *dst = c_priority_queue_create_capacity(
		src->opt.dump, src->opt.release, src->opt.compare, src->elem_size, src->capacity);
	if (dst == NULL)
	{
		return NULL;
	}

	int i = 0;
	elem_type elem = NULL;
	for (i = 1; i <= src->size; ++i)
	{
		elem = (elem_type)malloc(dst->elem_size);
		if (elem == NULL)
		{
			c_priority_queue_destroy(dst);
			return NULL;
		}
		dst->opt.dump(elem, src->elems[i], dst->elem_size);
		dst->elems[i] = elem;
	}

	dst->size = src->size;
	return dst;
}

void c_priority_queue_destroy(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return;
	}

	c_priority_queue_clear(pri_queue);

	int i = 0;
	for (i = 0; i <= pri_queue->capacity; ++i)
	{
		if (pri_queue->elems[i] != NULL)
		{
			free(pri_queue->elems[i]);
		}
	}

	free(pri_queue->elems);
	free(pri_queue);
}

const void* c_priority_queue_push(c_priority_queue *pri_queue, const void *elem)
{
	if (pri_queue == NULL || elem == NULL)
	{
		return NULL;
	}

	if (pri_queue->size >= pri_queue->capacity)
	{
		if (!c_priority_queue_reserve(pri_queue))
		{
			return NULL;
		}
	}

	int i = pri_queue->size + 1;
	elem_type new_elem = pri_queue->elems[i];
	if (new_elem == NULL)
	{
		new_elem = (elem_type)malloc(pri_queue->elem_size);
		if (new_elem == NULL)
		{
			return NULL;
		}
	}

	pri_queue->opt.dump(new_elem, elem, pri_queue->elem_size);
	
	for (; i != 1 && pri_queue->opt.compare(elem, pri_queue->elems[i/2]) < 0; i /= 2)
	{
		pri_queue->elems[i] = pri_queue->elems[i/2];
	}
	pri_queue->elems[i] = new_elem;
	++pri_queue->size;
	return new_elem;
}

void c_priority_queue_pop(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL || pri_queue->size == 0)
	{
		return;
	}

	int i = 0;
	int child = 0;
	elem_type min = pri_queue->elems[1];
	elem_type last = pri_queue->elems[pri_queue->size--];

	for (i = 1; i * 2 <= pri_queue->size; i = child)
	{
		child = i * 2;
		if (child < pri_queue->size &&
		    pri_queue->opt.compare(pri_queue->elems[child+1], pri_queue->elems[child]) < 0)
		{
			++child;
		}

		if (pri_queue->opt.compare(pri_queue->elems[child], last) < 0)
		{
			pri_queue->elems[i] = pri_queue->elems[child];
		}
		else
		{
			break;
		}
	}
	pri_queue->elems[i] = last;
	pri_queue->elems[pri_queue->size + 1] = min;
	pri_queue->opt.release(min);
}

void c_priority_queue_clear(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i <= pri_queue->size; ++i)
	{
		if (pri_queue->elems[i] != NULL)
		{
			pri_queue->opt.release(pri_queue->elems[i]);
		}
	}
	pri_queue->size = 0;
}

const void* c_priority_queue_top(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL || pri_queue->size == 0)
	{
		return NULL;
	}

	return pri_queue->elems[1];
}

int c_priority_queue_size(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return 0;
	}

	return pri_queue->size;
}

int c_priority_queue_is_empty(c_priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return 1;
	}

	return pri_queue->size == 0;
}
