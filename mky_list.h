#ifndef _MKY_LIST_H
#define _MKY_LIST_H

#include "mky_libdef.h"

struct mky_list_iter
{
	struct mky_list *lst;
	struct node *cur_node;
};
typedef struct mky_list_iter mky_list_iter;

typedef struct mky_list mky_list;

/**
 * Create a list
 * @param elem_size the size of element in the list
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return list pointer, or NULL when error
 */
mky_list* mky_list_create(size_t elem_size, compare_func comparator);

/**
 * Create a depth copy of this list instance.
 * @param src the source list
 * @return list pointer, or NULL when error
 */
mky_list* mky_list_clone(const mky_list *src);

/**
 * Clear the list, after the operation, all node will be free
 */
void mky_list_clear(mky_list *lst);

void mky_list_destroy(mky_list *lst);

/**
 * Adds a depth copy of specified element to the begin of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* mky_list_add_first(mky_list *lst, const void *elem);

/**
 * Appends a depth copy of specified element to the end of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* mky_list_add_last(mky_list *lst, const void *elem);

/**
 * Adds a depth copy specified element at the specified position in this list
 * After this operator the index of specified element is index
 * @return elem's point in list if adds successfully, or 0 when failed
 */
void* mky_list_add(mky_list *lst, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src list to the end of dst list
 * @return 1 if adds successfully, or 0 when failed
 */
int mky_list_add_all(mky_list *dst, const mky_list *src);

/**
 * Removes the first element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int mky_list_remove_first(mky_list *lst);

/**
 * Removes the last element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int mky_list_remove_last(mky_list *lst);

/**
 * Removes the first occurrence of the specified element from this list
 * @return 1 if removes successfully, or 0 when failed
 */
int mky_list_remove_elem(mky_list *lst, const void *elem);

/**
 * Removes the element at the specified position in this list
 * @return 1 if removes successfully, or 0 when failed
 */
int mky_list_remove(mky_list *lst, int index);

void* mky_list_get_first(const mky_list *lst);
void* mky_list_get_last(const mky_list *lst);
void* mky_list_get(const mky_list *lst, int index);

void mky_list_set_first(mky_list *lst, const void *elem);
void mky_list_set_last(mky_list *lst, const void *elem);
void mky_list_set(mky_list *lst, const void *elem, int index);

/**
 * Visit each elements in the list. if visitor return not 0, it will stop visiting.
 * @param lst will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @param extra_data save the result of visiting each elements
 */
void mky_list_foreach(mky_list *lst, visit_func vistor, void *extra_data);
int mky_list_find(const mky_list *lst, const void *elem, mky_list_iter *it);

int mky_list_size(const mky_list *lst);
int mky_list_is_empty(const mky_list *lst);

int mky_list_iter_init(mky_list *lst, mky_list_iter *it);
/**
 * Move iter to next position
 * @return the next element in the iteration
 */
void* mky_list_iter_next(mky_list_iter *it);
void* mky_list_iter_elem(const mky_list_iter *it);
int mky_list_iter_has_next(const mky_list_iter *it);
/**
 * Removes element which the current iter point to.
 */
void mky_list_iter_remove(mky_list_iter *it);
/**
 * Adds a depth copy specified element before the iter point to,
 * after this operation, param it point to the new elem in the list.
 */
void mky_list_iter_add(mky_list_iter *it, const void *elem);

#endif
