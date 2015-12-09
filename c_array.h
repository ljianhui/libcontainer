#ifndef _C_ARRAY_H
#define _C_ARRAY_H

#include "c_libdef.h"

struct c_array_iter
{
	struct c_array *a;
	int cur_index;
};
typedef struct c_array_iter c_array_iter;

typedef struct c_array c_array;

/**
 * Create a array
 * @param elem_size the size of element in the array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
c_array* c_array_create(size_t elem_size, compare_func comparator);

/**
 * Create a array with initial capacity, but size is zero
 * @param elem_size the size of element in the array
 * @param capacity the initial capacity of array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
c_array* c_array_create_capacity(
	size_t elem_size, int capacity, compare_func comparator);

/**
 * Create a depth copy of this array instance.
 * @param src the source array
 * @return array pointer, or NULL when error
 */
c_array* c_array_clone(const c_array *src);

/**
 * Clear the array, after the operation, size == 0
 */
void c_array_clear(c_array *a);

/**
 * Destroy the array
 */
void c_array_destroy(c_array *a);

/**
 * Appends a depth copy of specified element to the end of this array
 * @return elem's point in array if appends successfully, or 0 when failed 
 */
void* c_array_add_last(c_array *a, const void *elem);

/**
 * Removes the last element of array
 * @return 1 if remove successfully, or 0 when failed
 */
int c_array_remove_last(c_array *a);

/**
 * Adds a depth copy specified element at the specified position in this array
 * After this operator the index of specified element is index
 * @return elem's point in array if adds successfully, or 0 when failed
 */
void* c_array_add(c_array *a, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src array to the end of dst array
 * @return 1 if adds successfully, or 0 when failed
 */
int c_array_add_all(c_array *dst, const c_array *src);

/**
 * Removes the first occurrence of the specified element from this array
 * (Memory address or value of element equal to a element in the array)
 * @return 1 if adds successfully, or 0 when failed
 */
int c_array_remove_elem(c_array *a, const void *elem);

/**
 * Removes the element at the specified position in this array
 * @return 1 if adds successfully, or 0 when failed
 */
int c_array_remove(c_array *a, int index);

/**
 * Returns the element pointer at the specified position in this array
 */
void* c_array_get(const c_array *a, int index);

/**
 * Replaces the element at the specified position in this array
 * with a depth copy of specified element
 * @return 1 if set successfully, or 0 when failed
 */
int c_array_set(c_array *a, const void *elem, int index);

/**
 * Returns the index of the first occurrence of the specified element in this array,
 * or -1, if this array does not contain the element
 */
int c_array_index_of(const c_array *a, const void *elem);

/**
 * Visit each elements in the array. if visitor return not 0, it will stop visiting.
 * @param array will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @extra_data save the result of visiting each elements
 */
void c_array_foreach(
	c_array *a, visit_func vistor, void *extra_data);

/**
 * Returns 1 if this array contains no elements, otherwise return 0
 */
int c_array_is_empty(const c_array *a);

/**
 * Returns the number of elements in this array
 */
int c_array_size(const c_array *a);

/**
 * Returns the number of elements that the array will contain now
 */
int c_array_capacity(const c_array *a);

/**
 * Init array_iter, return 1 if success, otherwise return 0
 */
int c_array_iter_init(c_array *a, c_array_iter *it);

/**
 * Move iter to next position
 * @return the next element in the iteration
 */
void* c_array_iter_next(c_array_iter *it);

/**
 * Get the element data which the current iter point to
 */
void* c_array_iter_elem(c_array_iter *it);

/**
 * Returns 1 if the iteration has next element, otherwise return 0
 */
int c_array_iter_has_next(const c_array_iter *it);

/**
 * Removes element which the current iter point to.
 */
void c_array_iter_remove(c_array_iter *it);

#endif
