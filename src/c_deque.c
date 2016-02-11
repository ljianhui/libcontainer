#include <stdlib.h>
#include <memory.h>
#include "c_deque.h"
#include "c_list.h"

#define CQ_CAPACITY 128

struct circle_queue // fix circle queue
{
	// the circle queue is [begin,end)
	int begin; // index of first elem
	int end;   // index of after last elem
	char elems[0];
};
typedef struct circle_queue circle_queue;

typedef struct circle_queue_node circle_queue_node;

struct c_deque
{
	int elem_size;
	int size;
	c_list *cq_list;
};


static void* circle_queue_add_first(circle_queue *cq, const void *elem, size_t elem_size)
{
	--cq->begin;
	if (cq->begin < 0)
	{
		cq->begin = CQ_CAPACITY - 1;
	}

	void *dst = (void*)(cq->elems + elem_size * cq->begin);
	if (elem != C_ELEM_ZERO)
	{
		memcpy(dst, elem, elem_size);
	}
	else
	{
		memset(dst, 0, elem_size);
	}
	return dst;
}

static void* circle_queue_add_last(circle_queue *cq, const void *elem, size_t elem_size)
{
	void *dst = (void*)(cq->elems + elem_size * cq->end);
	if (elem != C_ELEM_ZERO)
	{
		memcpy(dst, elem, elem_size);
	}
	else
	{
		memset(dst, 0, elem_size);
	}

	++cq->end;
	if (cq->end == CQ_CAPACITY)
	{
		cq->end = 0;
	}
	return dst;
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

static void* circle_queue_first(const circle_queue *cq, size_t elem_size)
{
	if (cq == NULL)
	{
		return NULL;
	}
	return (void*)(cq->elems + elem_size * cq->begin);
}

static void* circle_queue_last(const circle_queue *cq, size_t elem_size)
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

c_deque* c_deque_create(size_t elem_size)
{
	if (elem_size == 0)
	{
		return NULL;
	}

	c_deque *deq = (c_deque*)malloc(sizeof(c_deque));
	if (deq == NULL)
	{
		return NULL;
	}

	deq->elem_size = elem_size;
	deq->size = 0;
	deq->cq_list = c_list_create(sizeof(circle_queue) + elem_size * CQ_CAPACITY, NULL);
	if (deq->cq_list == NULL)
	{
		free(deq);
		return NULL;
	}
	return deq;
}

c_deque* c_deque_clone(const c_deque *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	c_deque *dst = (c_deque*)malloc(sizeof(c_deque));
	if (dst == NULL)
	{
		return NULL;
	}

	dst->elem_size = src->elem_size;
	dst->size = src->size;
	dst->cq_list = c_list_clone(src->cq_list);

	if (dst->cq_list == NULL)
	{
		free(dst);
		return NULL;
	}
	
	return dst;
}

void c_deque_destroy(c_deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	c_list_destroy(deq->cq_list);
	free(deq);
}

void* c_deque_add_first(c_deque *deq, const void *elem)
{
	if (deq == NULL || elem == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)c_list_get_first(deq->cq_list);
	if (cq == NULL || cq->begin == cq->end)
	{
		cq = c_list_add_first(deq->cq_list, C_ELEM_ZERO);
		if (cq == NULL)
		{
			return NULL;
		}
	}

	void *cq_elem = circle_queue_add_first(cq, elem, deq->elem_size);
	++deq->size;
	return cq_elem;
}

void* c_deque_add_last(c_deque *deq, const void *elem)
{
	if (deq == NULL || elem == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)c_list_get_last(deq->cq_list);
	// if circle queue is full
	if (cq == NULL || cq->begin == cq->end)
	{
		cq = c_list_add_last(deq->cq_list, C_ELEM_ZERO);
		if (cq == NULL)
		{
			return NULL;
		}
	}

	void *cq_elem = circle_queue_add_last(cq, elem, deq->elem_size);
	++deq->size;
	return cq_elem;
}

int c_deque_remove_first(c_deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)c_list_get_first(deq->cq_list);
	circle_queue_remove_first(cq);
	if (cq->begin == cq->end)
	{
		c_list_remove_first(deq->cq_list);
	}
	--deq->size;
	return 1;
}

int c_deque_remove_last(c_deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)c_list_get_last(deq->cq_list);
	circle_queue_remove_last(cq);

	// if circle queue is empty
	if (cq->begin == cq->end)
	{
		c_list_remove_last(deq->cq_list);
	}
	--deq->size;
	return 1;
}

void c_deque_clear(c_deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	c_list_clear(deq->cq_list);
	deq->size = 0;
}

void* c_deque_get_first(const c_deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)c_list_get_first(deq->cq_list);
	return circle_queue_first(cq, deq->elem_size);
}

void* c_deque_get_last(const c_deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)c_list_get_last(deq->cq_list);
	return circle_queue_last(cq, deq->elem_size);
}

int c_deque_is_empty(const c_deque *deq)
{
	if (deq == NULL)
	{
		return 1;
	}

	return deq->size == 0;
}

int c_deque_size(const c_deque *deq)
{
	if (deq == NULL)
	{
		return 0;
	}

	return deq->size;
}
