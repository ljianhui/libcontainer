#include <stdlib.h>
#include <memory.h>
#include "priority_queue.h"
#include <stdio.h>

// The index of elems begin from 1, not 0

#define MIN_PRI_QUEUE_SIZE 16

typedef void* elem_type;

struct priority_queue
{
    elem_type *elems;
    int elem_size;
    int size;
    int capacity;
    compare_func comparator;
};

static int reserve(priority_queue *pri_queue)
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

static priority_queue* create_priority_queue(size_t elem_size, compare_func comparator, int capacity)
{
	if (comparator == NULL || elem_size == 0 || capacity <= 0)
	{
		return NULL;
	}

	priority_queue *pri_queue = (priority_queue*)malloc(sizeof(priority_queue));
	if (pri_queue == NULL)
	{
		return NULL;
	}

	pri_queue->elems = (elem_type*)malloc(sizeof(elem_size) * (capacity + 1));
	if (pri_queue->elems == NULL)
	{
		free(pri_queue);
		return NULL;
	}

	memset(pri_queue->elems, 0, sizeof(elem_type) * (capacity + 1));
	pri_queue->elem_size = elem_size;
	pri_queue->size = 0;
	pri_queue->capacity = capacity;
	pri_queue->comparator = comparator;
	return pri_queue;
}

priority_queue* priority_queue_create(size_t elem_size, compare_func comparator)
{
	return create_priority_queue(elem_size, comparator, MIN_PRI_QUEUE_SIZE);
}

priority_queue* priority_queue_clone(const priority_queue *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	priority_queue *dst = create_priority_queue(src->elem_size, src->comparator, src->capacity);
	if (dst == NULL)
	{
		return NULL;
	}

	int i = 0;
	elem_type elem = NULL;
	for (i = 1; i <= src->size; ++i)
	{
		elem = (elem_type)malloc(src->elem_size);
		if (elem == NULL)
		{
			priority_queue_destroy(dst);
			return NULL;
		}
		memcpy(elem, src->elems[i], src->elem_size);
		dst->elems[i] = elem;
	}

	dst->size = src->size;
	return dst;
}

void priority_queue_destroy(priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return;
	}

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

int priority_queue_push(priority_queue *pri_queue, const void *elem)
{
	if (pri_queue == NULL || elem == NULL)
	{
		return 0;
	}

	if (pri_queue->size >= pri_queue->capacity)
	{
		if (!reserve(pri_queue))
		{
			return 0;
		}
	}

	int i = pri_queue->size + 1;
	elem_type new_elem = pri_queue->elems[i];
	if (new_elem == NULL)
	{
		new_elem = (elem_type)malloc(pri_queue->elem_size);
		if (new_elem == NULL)
		{
			return 0;
		}
	}
	memcpy(new_elem, elem, pri_queue->elem_size);

	for (; i != 1 && pri_queue->comparator(elem, pri_queue->elems[i/2]) < 0; i /= 2)
    {
        pri_queue->elems[i] = pri_queue->elems[i/2];
    }
    pri_queue->elems[i] = new_elem;
    ++pri_queue->size;
    return 1;
}

void priority_queue_pop(priority_queue *pri_queue)
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
            pri_queue->comparator(pri_queue->elems[child+1], pri_queue->elems[child]) < 0)
        {
            ++child;
        }

        if (pri_queue->comparator(pri_queue->elems[child], last) < 0)
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
}

void priority_queue_clear(priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return;
	}

	pri_queue->size = 0;
}

void* priority_queue_top(priority_queue *pri_queue)
{
	if (pri_queue == NULL || pri_queue->size == 0)
	{
		return NULL;
	}

	return pri_queue->elems[1];
}

int priority_queue_size(priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return 0;
	}

	return pri_queue->size;
}

int priority_queue_is_empty(priority_queue *pri_queue)
{
	if (pri_queue == NULL)
	{
		return 1;
	}

	return pri_queue->size == 0;
}
