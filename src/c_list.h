#ifndef _C_LIST_H
#define _C_LIST_H

#include "c_libdef.h"

struct c_list_iter
{
	struct c_list *lst;
	struct c_list_node *cur_node;
};
typedef struct c_list_iter c_list_iter;

typedef struct c_list c_list;

/**
 * Create a list
 * @param elem_size the size of element in the list
 * @return list pointer, or NULL when error
 */
c_list* c_list_create(dump_func dump, release_func release, compare_func compare, size_t elem_size);

/**
 * Create a depth copy of this list instance.
 * @param src the source list
 * @return list pointer, or NULL when error
 */
c_list* c_list_clone(const c_list *src);

/**
 * Clear the list, after the operation, all node will be free
 */
void c_list_clear(c_list *lst);

void c_list_destroy(c_list *lst);

/**
 * Adds a depth copy of specified element to the begin of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* c_list_add_first(c_list *lst, const void *elem);

/**
 * Appends a depth copy of specified element to the end of this list
 * @return elem's point in list if appends successfully, or 0 when failed 
 */
void* c_list_add_last(c_list *lst, const void *elem);

/**
 * Adds a depth copy specified element at the specified position in this list
 * After this operator the index of specified element is index
 * @return elem's point in list if adds successfully, or 0 when failed
 */
void* c_list_add(c_list *lst, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src list to the end of dst list
 * @return 1 if adds successfully, or 0 when failed
 */
int c_list_add_all(c_list *dst, const c_list *src);

/**
 * Removes the first element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int c_list_remove_first(c_list *lst);

/**
 * Removes the last element of list
 * @return 1 if remove successfully, or 0 when failed
 */
int c_list_remove_last(c_list *lst);

/**
 * Removes the first occurrence of the specified element from this list
 * @return 1 if removes successfully, or 0 when failed
 */
int c_list_remove_elem(c_list *lst, const void *elem);

/**
 * Removes the element at the specified position in this list
 * @return 1 if removes successfully, or 0 when failed
 */
int c_list_remove(c_list *lst, int index);

void* c_list_get_first(const c_list *lst);
void* c_list_get_last(const c_list *lst);
void* c_list_get(const c_list *lst, int index);

void c_list_set_first(c_list *lst, const void *elem);
void c_list_set_last(c_list *lst, const void *elem);
void c_list_set(c_list *lst, const void *elem, int index);

/**
 * Visit each elements in the list. if visitor return not 0, it will stop visiting.
 * @param lst will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @param extra_data save the result of visiting each elements
 */
void c_list_foreach(c_list *lst, visit_func vistor, void *extra_data);
void c_list_find(const c_list *lst, const void *elem, c_list_iter *it);

int c_list_size(const c_list *lst);
int c_list_is_empty(const c_list *lst);

int c_list_iter_init(c_list *lst, c_list_iter *it);
/**
 * Move iter to next position
 * @return the next element in the iteration
 */
void* c_list_iter_next(c_list_iter *it);
void* c_list_iter_elem(const c_list_iter *it);
int c_list_iter_has_next(const c_list_iter *it);
/**
 * Removes element which the current iter point to.
 */
void c_list_iter_remove(c_list_iter *it);
/**
 * Adds a depth copy specified element before the iter point to,
 * after this operation, param it point to the new elem in the list.
 */
void c_list_iter_add(c_list_iter *it, const void *elem);

#endif
