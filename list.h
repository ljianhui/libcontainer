#ifndef _LIST_H
#define _LIST_H

#include "libdef.h"

struct list_iterator
{
	struct list *lst;
	struct node *cur_node;
};
typedef struct list_iterator list_iterator;

typedef struct list list;

/**
 * Create a list
 * @param elem_size the size of element in the list
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return list pointer, or NULL when error
 */
list* list_create(size_t elem_size, compare_func comparator);

/**
 * Create a depth copy of this list instance.
 * @param src the source list
 * @return list pointer, or NULL when error
 */
list* list_clone(const list *src);

/**
 * Clear the list, after the operation, all node will be free
 */
void list_clear(list *lst);

void list_destroy(list *lst);

/**
 * Adds a depth copy of specified element to the begin of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* list_add_first(list *lst, const void *elem);

/**
 * Appends a depth copy of specified element to the end of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* list_add_last(list *lst, const void *elem);

/**
 * Adds a depth copy specified element at the specified position in this list
 * After this operator the index of specified element is index
 * @return elem's point in list if adds successfully, or 0 when failed
 */
void* list_add(list *lst, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src list to the end of dst list
 * @return 1 if adds successfully, or 0 when failed
 */
int list_add_all(list *dst, const list *src);

/**
 * Removes the first element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int list_remove_first(list *lst);

/**
 * Removes the last element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int list_remove_last(list *lst);

/**
 * Removes the first occurrence of the specified element from this list
 * @return 1 if removes successfully, or 0 when failed
 */
int list_remove_elem(list *lst, const void *elem);

/**
 * Removes the element at the specified position in this list
 * @return 1 if removes successfully, or 0 when failed
 */
int list_remove(list *lst, int index);

void* list_get_first(const list *lst);
void* list_get_last(const list *lst);
void* list_get(const list *lst, int index);

void list_set_first(list *lst, const void *elem);
void list_set_last(list *lst, const void *elem);
void list_set(list *lst, const void *elem, int index);

/**
 * Visit each elements in the list. if visitor return not 0, it will stop visiting.
 * @param lst will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @param extra_data save the result of visiting each elements
 */
void list_foreach(list *lst, visit_func vistor, void *extra_data);
int list_find(const list *lst, const void *elem, list_iterator *it);

int list_size(const list *lst);
int list_is_empty(const list *lst);

int list_iterator_init(list *lst, list_iterator *it);
/**
 * Move iterator to next position
 * @return the next element in the iteration
 */
void* list_iterator_next(list_iterator *it);
void* list_iterator_elem(const list_iterator *it);
int list_iterator_has_next(const list_iterator *it);
/**
 * Removes element which the current iterator point to.
 */
void list_iterator_remove(list_iterator *it);
/**
 * Adds a depth copy specified element before the iterator point to,
 * after this operation, param it point to the new elem in the list.
 */
void list_iterator_add(list_iterator *it, const void *elem);

#endif
