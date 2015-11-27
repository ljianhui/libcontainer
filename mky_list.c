#include <stdlib.h>
#include <memory.h>
#include "mky_list.h"

struct node
{
	struct node *prev;
	struct node *next;
	char elem[0];
};
typedef struct node node;

struct mky_list
{
	struct node *head;
	compare_func comparator;
	size_t elem_size;
	int size;
};


static node* create_node(const void *elem, size_t elem_size)
{
	node *nd = (node*)malloc(sizeof(struct node) + elem_size);
	if (nd == NULL)
	{
		return NULL;
	}

	if (elem != NULL)
	{
		memcpy(nd->elem, elem, elem_size);
	}
	else
	{
		memset(nd->elem, 0, elem_size);
	}
	nd->prev = nd->next = NULL;
	return nd;
}

static void link_to_mky_list(mky_list *lst, node *x, node *y)
{
	x->prev = y->prev;
	y->prev->next = x;
	x->next = y;
	y->prev = x;
	++lst->size;
}

static node* find_node(const mky_list *lst, int index)
{
	int i = 0;
	node *nd = lst->head;
	if (index <= lst->size/2)
	{
		for (i = 0; i <= index; ++i)
		{
			nd = nd->next;
		}
	}
	else
	{
		for (i = lst->size; i > index; --i)
		{
			nd = nd->prev;
		}
	}
	return nd;
}

static void unlink_from_mky_list(mky_list *lst, node *nd)
{
	if (lst->head == nd)
	{
		return;
	}

	nd->next->prev = nd->prev;
	nd->prev->next = nd->next;

	free(nd);
	--lst->size;
}

mky_list* mky_list_create(size_t elem_size, compare_func comparator)
{
	if (elem_size == 0)
	{
		return NULL;
	}

	mky_list *lst = (mky_list*)malloc(sizeof(struct mky_list));
	if (lst == NULL)
	{
		return NULL;
	}

	node *head = (node*)malloc(sizeof(struct node));
	if (head == NULL)
	{
		free(lst);
		return NULL;
	}

	head->prev = head;
	head->next = head;

	lst->head = head;
	lst->comparator = comparator;
	lst->elem_size = elem_size;
	lst->size = 0;
}

mky_list* mky_list_clone(const mky_list *src)
{
	if (src == NULL)
	{
		return NULL;
	}

	mky_list *dst = mky_list_create(src->elem_size, src->comparator);
	if (dst == NULL)
	{
		return NULL;
	}

	node *src_node = src->head->next;
	node *dst_node = NULL;
	while (src_node != src->head)
	{
		dst_node = create_node(src_node->elem, src->elem_size);
		if (dst_node == NULL)
		{
			mky_list_destroy(dst);
			return NULL;
		}
		link_to_mky_list(dst, dst_node, dst->head);
		src_node = src_node->next;
	}
	return dst;
}

void mky_list_clear(mky_list *lst)
{
	if (lst == NULL)
	{
		return;
	}

	node *free_node = lst->head->next;
	node *next_node = free_node->next;
	while (free_node != lst->head)
	{
		free(free_node);
		free_node = next_node;
		next_node = next_node->next;
	}
	lst->head->prev = lst->head->next = lst->head;
	lst->size = 0;
}

void mky_list_destroy(mky_list *lst)
{
	if (lst == NULL)
	{
		return;
	}
	mky_list_clear(lst);
	free(lst->head);
	free(lst);
}

void* mky_list_add_first(mky_list *lst, const void *elem)
{
	if (lst == NULL)
	{
		return NULL;
	}

	node *nd = create_node(elem, lst->elem_size);
	if (nd == NULL)
	{
		return NULL;
	}

	link_to_mky_list(lst, nd, lst->head->next);
	return nd->elem;
}

void* mky_list_add_last(mky_list *lst, const void *elem)
{
	if (lst == NULL)
	{
		return NULL;
	}

	node *nd = create_node(elem, lst->elem_size);
	if (nd == NULL)
	{
		return NULL;
	}

	link_to_mky_list(lst, nd, lst->head);
	return nd->elem;
}

void* mky_list_add(mky_list *lst, const void *elem, int index)
{
	if (lst == NULL || index < 0 || index > lst->size)
	{
		return NULL;
	}

	node *nd = create_node(elem, lst->elem_size);
	if (nd == NULL)
	{
		return NULL;
	}

	node *pos = find_node(lst, index);
	link_to_mky_list(lst, nd, pos);
	return nd->elem;
}

int mky_list_add_all(mky_list *dst, const mky_list *src)
{
	if (dst == NULL || src == NULL)
	{
		return 0;
	}

	if (src->size == 0)
	{
		return 1;
	}

	mky_list *tmp = mky_list_clone(src);
	if (tmp == NULL)
	{
		return 0;
	}

	tmp->head->prev->next = dst->head;
	dst->head->prev->next = tmp->head->next;
	tmp->head->next->prev = dst->head->prev;
	dst->head->prev = tmp->head->prev;

	tmp->head->next = tmp->head;
	tmp->head->prev = tmp->head;
	mky_list_destroy(tmp);

	dst->size += src->size;
	return 1;
}

int mky_list_remove_first(mky_list *lst)
{
	if (lst == NULL || lst->size == 0)
	{
		return 0;
	}

	unlink_from_mky_list(lst, lst->head->next);
	return 1;
}

int mky_list_remove_last(mky_list *lst)
{
	if (lst == NULL || lst->size == 0)
	{
		return 0;
	}

	unlink_from_mky_list(lst, lst->head->prev);
	return 1;
}

int mky_list_remove_elem(mky_list *lst, const void *elem)
{
	if (lst == NULL || elem == NULL || lst->comparator == NULL)
	{
		return 0;
	}

	node *nd = lst->head->next;
	node *next = NULL;
	while (nd != lst->head)
	{
		if (lst->comparator(nd->elem, elem) == 0)
		{
			unlink_from_mky_list(lst, nd);
			return 1;
		}
		nd = nd->next;
	}
	return 0;
}

int mky_list_remove(mky_list *lst, int index)
{
	if (lst == NULL || index < 0 || index > lst->size)
	{
		return 0;
	}

	node *nd = find_node(lst, index);
	unlink_from_mky_list(lst, nd);
	return 1;
}

void* mky_list_get_first(const mky_list *lst)
{
	if (lst == NULL || lst->size == 0)
	{
		return NULL;
	}

	return (void*)lst->head->next->elem;
}

void* mky_list_get_last(const mky_list *lst)
{
	if (lst == NULL || lst->size == 0)
	{
		return NULL;
	}

	return (void*)lst->head->prev->elem;
}

void* mky_list_get(const mky_list *lst, int index)
{
	if (lst == NULL || index < 0 || index >= lst->size)
	{
		return NULL;
	}

	node *nd = find_node(lst, index);
	return (void*)nd->elem;
}

void mky_list_set_first(mky_list *lst, const void *elem)
{
	if (lst == NULL || lst->size == 0 || elem == NULL)
	{
		return;
	}

	memcpy(lst->head->next->elem, elem, lst->elem_size);
}

void mky_list_set_last(mky_list *lst, const void *elem)
{
	if (lst == NULL || lst->size == 0 || elem == NULL)
	{
		return;
	}

	memcpy(lst->head->prev->elem, elem, lst->elem_size);
}

void mky_list_set(mky_list *lst, const void *elem, int index)
{
	if (lst == NULL || index < 0 || index >= lst->size)
	{
		return;
	}

	node *nd = find_node(lst, index);
	if (nd == lst->head)
	{
		return;
	}

	memcpy(nd->elem, elem, lst->elem_size);
}

void mky_list_foreach(mky_list *lst, visit_func vistor, void *extra_data)
{
	if (lst == NULL || vistor == NULL)
	{
		return;
	}

	node *nd = lst->head->next;
	while (nd != lst->head)
	{
		if (vistor((void*)nd->elem, extra_data))
		{
			break;
		}
		nd = nd->next;
	}
}

int mky_list_find(const mky_list *lst, const void *elem, mky_list_iter *it)
{
	if (lst == NULL || lst->comparator == NULL || elem == NULL)
	{
		return 0;
	}

	node *nd = lst->head->next;
	while (nd != lst->head)
	{
		if (lst->comparator(nd->elem, elem) == 0)
		{
			if (it != NULL)
			{
				it->lst = (mky_list*)lst;
				it->cur_node = nd;
			}
			return 1;
		}
		nd = nd->next;
	}
	return 0;
}

int mky_list_size(const mky_list *lst)
{
	return lst->size;
}

int mky_list_is_empty(const mky_list *lst)
{
	return lst->size == 0;
}

int mky_list_iter_init(mky_list *lst, mky_list_iter *it)
{
	if (it == NULL)
	{
		return 0;
	}

	it->lst = lst;
	it->cur_node = lst != NULL ? lst->head : NULL;
	return 1;
}

void* mky_list_iter_next(mky_list_iter *it)
{
	// if it->lst == NULL, it->cur_node is NULL too.
	if (!mky_list_iter_has_next(it))
	{
		return NULL;
	}

	it->cur_node = it->cur_node->next;
	return (void*)(it->cur_node->elem);
}

void* mky_list_iter_elem(const mky_list_iter *it)
{
	if (it == NULL || it->cur_node == NULL)
	{
		return NULL;
	}

	return (void*)(it->cur_node->elem);
}

int mky_list_iter_has_next(const mky_list_iter *it)
{
	if (it == NULL || it->cur_node == NULL)
	{
		return 0;
	}

	return it->cur_node->next != it->lst->head;
}

void mky_list_iter_remove(mky_list_iter *it)
{
	if (it == NULL || it->cur_node == NULL)
	{
		return;
	}

	node *nd = it->cur_node->prev;
	unlink_from_mky_list(it->lst, it->cur_node);
	it->cur_node = nd;
}

void mky_list_iter_add(mky_list_iter *it, const void *elem)
{
	if (it == NULL || it->cur_node == NULL)
	{
		return;
	}

	node *nd = create_node(elem, it->lst->elem_size);
	if (nd == NULL)
	{
		return;
	}

	link_to_mky_list(it->lst, nd, it->cur_node);
	it->cur_node = nd;
}
