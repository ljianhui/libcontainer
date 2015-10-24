#include <stdlib.h>
#include <memory.h>
#include "deque.h"
#include "list.h"

#define CQ_CAPACITY 64

struct circle_queue // fix circle queue
{
	// the circle queue is [begin,end)
	int begin; // index of first elem
	int end;   // index of after last elem
	char elems[0];
};
typedef struct circle_queue circle_queue;

typedef struct circle_queue_node circle_queue_node;

struct deque
{
	int elem_size;
	int size;
	list *cq_list; // single circle list of circle queue
};


static void circle_queue_add_first(circle_queue *cq, const void *elem, size_t elem_size)
{
	--cq->begin;
	if (cq->begin < 0)
	{
		cq->begin = CQ_CAPACITY - 1;
	}
	if (elem != NULL)
	{
		memcpy(cq->elems + elem_size * cq->begin, elem, elem_size);
	}
	else
	{
		memset(cq->elems + elem_size * cq->begin, 0, elem_size);
	}
}

static void circle_queue_append(circle_queue *cq, const void *elem, size_t elem_size)
{
	if (elem != NULL)
	{
		memcpy(cq->elems + elem_size * cq->end, elem, elem_size);
	}
	else
	{
		memset(cq->elems + elem_size * cq->end, 0, elem_size);
	}

	++cq->end;
	if (cq->end == CQ_CAPACITY)
	{
		cq->end = 0;
	}
}

static void circle_queue_remove_first(circle_queue *cq)
{
	++cq->begin;
	if (cq->begin == CQ_CAPACITY)
	{
		cq->begin = 0;
	}
}

static void circle_queue_remove_last(circle_queue *cq)
{
	--cq->end;
	if (cq->end < 0)
	{
		cq->end = CQ_CAPACITY - 1;
	}
}

static void* circle_queue_first(circle_queue *cq, size_t elem_size)
{
	if (cq == NULL)
	{
		return NULL;
	}
	return (void*)(cq->elems + elem_size * cq->begin);
}

static void* circle_queue_last(circle_queue *cq, size_t elem_size)
{
	if (cq == NULL)
	{
		return NULL;
	}

	int index = cq->end - 1;
	if (index < 0)
	{
		index = CQ_CAPACITY - 1;
	}
	return (void*)(cq->elems + elem_size * index);
}

deque* deque_create(size_t elem_size)
{
	if (elem_size == 0)
	{
		return NULL;
	}

	deque *deq = (deque*)malloc(sizeof(deque));
	if (deq == NULL)
	{
		return NULL;
	}

	deq->elem_size = elem_size;
	deq->size = 0;
	deq->cq_list = list_create(sizeof(circle_queue) + elem_size * CQ_CAPACITY, NULL);
	if (deq->cq_list == NULL)
	{
		free(deq);
		return NULL;
	}
	return deq;
}

deque* deque_clone(const deque *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	deque *dst = (deque*)malloc(sizeof(deque));
	if (dst == NULL)
	{
		return NULL;
	}

	dst->elem_size = src->elem_size;
	dst->size = src->size;
	dst->cq_list = list_clone(src->cq_list);

	if (dst->cq_list == NULL)
	{
		free(dst);
		return NULL;
	}
	
	return dst;
}

void deque_destroy(deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	list_destroy(deq->cq_list);
	free(deq);
}

int deque_add_first(deque *deq, const void *elem)
{
	if (deq == NULL)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)list_get_first(deq->cq_list);
	if (cq == NULL || cq->begin == cq->end)
	{
		if (list_add_first(deq->cq_list, NULL))
		{
			cq = (circle_queue*)list_get_first(deq->cq_list);
		}
		else
		{
			return 0;
		}
	}

	circle_queue_add_first(cq, elem, deq->elem_size);
	++deq->size;
	return 1;
}

int deque_append(deque *deq, const void *elem)
{
	if (deq == NULL)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)list_get_last(deq->cq_list);
	// if circle queue is full
	if (cq == NULL || cq->begin == cq->end)
	{
		if (list_append(deq->cq_list, NULL))
		{
			cq = (circle_queue*)list_get_last(deq->cq_list);
		}
		else
		{
			return 0;
		}
	}

	circle_queue_append(cq, elem, deq->elem_size);
	++deq->size;
	return 1;
}

int deque_remove_first(deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)list_get_first(deq->cq_list);
	circle_queue_remove_first(cq);
	if (cq->begin == cq->end)
	{
		list_remove_first(deq->cq_list);
	}
	--deq->size;
	return 1;
}

int deque_remove_last(deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)list_get_last(deq->cq_list);
	circle_queue_remove_last(cq);

	// if circle queue is empty
	if (cq->begin == cq->end)
	{
		list_remove_last(deq->cq_list);
	}
	--deq->size;
	return 1;
}

void deque_clear(deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	list_clear(deq->cq_list);
	deq->size = 0;
}

void* deque_first(deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)list_get_first(deq->cq_list);
	return circle_queue_first(cq, deq->elem_size);
}

void* deque_last(deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)list_get_last(deq->cq_list);
	return circle_queue_last(cq, deq->elem_size);
}

int deque_is_empty(const deque *deq)
{
	if (deq == NULL)
	{
		return 1;
	}

	return deq->size == 0;
}

int deque_size(const deque *deq)
{
	if (deq == NULL)
	{
		return 0;
	}

	return deq->size;
}
