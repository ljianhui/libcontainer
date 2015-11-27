#include <stdlib.h>
#include <memory.h>
#include "mky_deque.h"
#include "mky_list.h"

#define CQ_CAPACITY 2

struct circle_queue // fix circle queue
{
	// the circle queue is [begin,end)
	int begin; // index of first elem
	int end;   // index of after last elem
	char elems[0];
};
typedef struct circle_queue circle_queue;

typedef struct circle_queue_node circle_queue_node;

struct mky_deque
{
	int elem_size;
	int size;
	mky_list *cq_list; // single circle list of circle queue
};


static void* circle_queue_add_first(circle_queue *cq, const void *elem, size_t elem_size)
{
	--cq->begin;
	if (cq->begin < 0)
	{
		cq->begin = CQ_CAPACITY - 1;
	}

	void *dst = (void*)(cq->elems + elem_size * cq->begin);
	if (elem != NULL)
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
	if (elem != NULL)
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

mky_deque* mky_deque_create(size_t elem_size)
{
	if (elem_size == 0)
	{
		return NULL;
	}

	mky_deque *deq = (mky_deque*)malloc(sizeof(mky_deque));
	if (deq == NULL)
	{
		return NULL;
	}

	deq->elem_size = elem_size;
	deq->size = 0;
	deq->cq_list = mky_list_create(sizeof(circle_queue) + elem_size * CQ_CAPACITY, NULL);
	if (deq->cq_list == NULL)
	{
		free(deq);
		return NULL;
	}
	return deq;
}

mky_deque* mky_deque_clone(const mky_deque *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	mky_deque *dst = (mky_deque*)malloc(sizeof(mky_deque));
	if (dst == NULL)
	{
		return NULL;
	}

	dst->elem_size = src->elem_size;
	dst->size = src->size;
	dst->cq_list = mky_list_clone(src->cq_list);

	if (dst->cq_list == NULL)
	{
		free(dst);
		return NULL;
	}
	
	return dst;
}

void mky_deque_destroy(mky_deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	mky_list_destroy(deq->cq_list);
	free(deq);
}

void* mky_deque_add_first(mky_deque *deq, const void *elem)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_first(deq->cq_list);
	if (cq == NULL || cq->begin == cq->end)
	{
		if (mky_list_add_first(deq->cq_list, NULL))
		{
			cq = (circle_queue*)mky_list_get_first(deq->cq_list);
		}
		else
		{
			return NULL;
		}
	}

	void *cq_elem = circle_queue_add_first(cq, elem, deq->elem_size);
	++deq->size;
	return cq_elem;
}

void* mky_deque_add_last(mky_deque *deq, const void *elem)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_last(deq->cq_list);
	// if circle queue is full
	if (cq == NULL || cq->begin == cq->end)
	{
		if (mky_list_add_last(deq->cq_list, NULL))
		{
			cq = (circle_queue*)mky_list_get_last(deq->cq_list);
		}
		else
		{
			return NULL;
		}
	}

	void *cq_elem = circle_queue_add_last(cq, elem, deq->elem_size);
	++deq->size;
	return cq_elem;
}

int mky_deque_remove_first(mky_deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_first(deq->cq_list);
	circle_queue_remove_first(cq);
	if (cq->begin == cq->end)
	{
		mky_list_remove_first(deq->cq_list);
	}
	--deq->size;
	return 1;
}

int mky_deque_remove_last(mky_deque *deq)
{
	if (deq == NULL || deq->size == 0)
	{
		return 0;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_last(deq->cq_list);
	circle_queue_remove_last(cq);

	// if circle queue is empty
	if (cq->begin == cq->end)
	{
		mky_list_remove_last(deq->cq_list);
	}
	--deq->size;
	return 1;
}

void mky_deque_clear(mky_deque *deq)
{
	if (deq == NULL)
	{
		return;
	}

	mky_list_clear(deq->cq_list);
	deq->size = 0;
}

void* mky_deque_get_first(const mky_deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_first(deq->cq_list);
	return circle_queue_first(cq, deq->elem_size);
}

void* mky_deque_get_last(const mky_deque *deq)
{
	if (deq == NULL)
	{
		return NULL;
	}

	circle_queue *cq = (circle_queue*)mky_list_get_last(deq->cq_list);
	return circle_queue_last(cq, deq->elem_size);
}

int mky_deque_is_empty(const mky_deque *deq)
{
	if (deq == NULL)
	{
		return 1;
	}

	return deq->size == 0;
}

int mky_deque_size(const mky_deque *deq)
{
	if (deq == NULL)
	{
		return 0;
	}

	return deq->size;
}
