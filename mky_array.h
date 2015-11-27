#ifndef _MKY_ARRAY_H
#define _MKY_ARRAY_H

#include "mky_libdef.h"

struct mky_array_iter
{
	struct mky_array *a;
	int cur_index;
};
typedef struct mky_array_iter mky_array_iter;

typedef struct mky_array mky_array;

/**
 * Create a array
 * @param elem_size the size of element in the array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
mky_array* mky_array_create(size_t elem_size, compare_func comparator);

/**
 * Create a array with initial capacity, but size is zero
 * @param elem_size the size of element in the array
 * @param capacity the initial capacity of array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
mky_array* mky_array_create_capacity(
	size_t elem_size, int capacity, compare_func comparator);

/**
 * Create a depth copy of this array instance.
 * @param src the source array
 * @return array pointer, or NULL when error
 */
mky_array* mky_array_clone(const mky_array *src);

/**
 * Clear the array, after the operation, size == 0
 */
void mky_array_clear(mky_array *a);

/**
 * Destroy the array
 */
void mky_array_destroy(mky_array *a);

/**
 * Appends a depth copy of specified element to the end of this array
 * @return elem's point in array if appends successfully, or 0 when failed 
 */
void* mky_array_add_last(mky_array *a, const void *elem);

/**
 * Removes the last element of array
 * @return 1 if remove successfully, or 0 when failed
 */
int mky_array_remove_last(mky_array *a);

/**
 * Adds a depth copy specified element at the specified position in this array
 * After this operator the index of specified element is index
 * @return elem's point in array if adds successfully, or 0 when failed
 */
void* mky_array_add(mky_array *a, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src array to the end of dst array
 * @return 1 if adds successfully, or 0 when failed
 */
int mky_array_add_all(mky_array *dst, const mky_array *src);

/**
 * Removes the first occurrence of the specified element from this array
 * (Memory address or value of element equal to a element in the array)
 * @return 1 if adds successfully, or 0 when failed
 */
int mky_array_remove_elem(mky_array *a, const void *elem);

/**
 * Removes the element at the specified position in this array
 * @return 1 if adds successfully, or 0 when failed
 */
int mky_array_remove(mky_array *a, int index);

/**
 * Returns the element pointer at the specified position in this array
 */
void* mky_array_get(const mky_array *a, int index);

/**
 * Replaces the element at the specified position in this array
 * with a depth copy of specified element
 * @return 1 if set successfully, or 0 when failed
 */
int mky_array_set(mky_array *a, const void *elem, int index);

/**
 * Returns the index of the first occurrence of the specified element in this array,
 * or -1, if this array does not contain the element
 */
int mky_array_index_of(const mky_array *a, const void *elem);

/**
 * Visit each elements in the array. if visitor return not 0, it will stop visiting.
 * @param array will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @extra_data save the result of visiting each elements
 */
void mky_array_foreach(
	mky_array *a, visit_func vistor, void *extra_data);

/**
 * Returns 1 if this array contains no elements, otherwise return 0
 */
int mky_array_is_empty(const mky_array *a);

/**
 * Returns the number of elements in this array
 */
int mky_array_size(const mky_array *a);

/**
 * Returns the number of elements that the array will contain now
 */
int mky_array_capacity(const mky_array *a);

/**
 * Init array_iter, return 1 if success, otherwise return 0
 */
int mky_array_iter_init(mky_array *a, mky_array_iter *it);

/**
 * Move iter to next position
 * @return the next element in the iteration
 */
void* mky_array_iter_next(mky_array_iter *it);

/**
 * Get the element data which the current iter point to
 */
void* mky_array_iter_elem(mky_array_iter *it);

/**
 * Returns 1 if the iteration has next element, otherwise return 0
 */
int mky_array_iter_has_next(const mky_array_iter *it);

/**
 * Removes element which the current iter point to.
 */
void mky_array_iter_remove(mky_array_iter *it);

#endif
