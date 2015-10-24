#ifndef _ARRAY_H
#define _ARRAY_H

#include "libdef.h"

struct array_iterator
{
	struct array *a;
	int cur_index;
};
typedef struct array_iterator array_iterator;

typedef struct array array;

/**
 * Create a array
 * @param elem_size the size of element in the array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
array* array_create(size_t elem_size, compare_func comparator);

/**
 * Create a array with initial capacity, but size is zero
 * @param elem_size the size of element in the array
 * @param capacity the initial capacity of array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
array* array_create_capacity(
	size_t elem_size, int capacity, compare_func comparator);

/**
 * Create a depth copy of this array instance.
 * @param src the source array
 * @return array pointer, or NULL when error
 */
array* array_clone(const array *src);

/**
 * Clear the array, after the operation, size == 0
 */
void array_clear(array *a);

/**
 * Destroy the array
 */
void array_destroy(array *a);

/**
 * Appends a depth copy of specified element to the end of this array
 * @return elem's point in array if appends successfully, or 0 when failed 
 */
void* array_add_last(array *a, const void *elem);

/**
 * Removes the last element of array
 * @return 1 if remove successfully, or 0 when failed
 */
int array_remove_last(array *a);

/**
 * Adds a depth copy specified element at the specified position in this array
 * After this operator the index of specified element is index
 * @return elem's point in array if adds successfully, or 0 when failed
 */
void* array_add(array *a, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src array to the end of dst array
 * @return 1 if adds successfully, or 0 when failed
 */
int array_add_all(array *dst, const array *src);

/**
 * Removes the first occurrence of the specified element from this array
 * (Memory address or value of element equal to a element in the array)
 * @return 1 if adds successfully, or 0 when failed
 */
int array_remove_elem(array *a, const void *elem);

/**
 * Removes the element at the specified position in this array
 * @return 1 if adds successfully, or 0 when failed
 */
int array_remove(array *a, int index);

/**
 * Returns the element pointer at the specified position in this array
 */
void* array_get(const array *a, int index);

/**
 * Replaces the element at the specified position in this array
 * with a depth copy of specified element
 * @return 1 if set successfully, or 0 when failed
 */
int array_set(array *a, const void *elem, int index);

/**
 * Returns the index of the first occurrence of the specified element in this array,
 * or -1, if this array does not contain the element
 */
int array_index_of(const array *a, const void *elem);

/**
 * Visit each elements in the array. if visitor return not 0, it will stop visiting.
 * @param array will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @extra_data save the result of visiting each elements
 */
void array_foreach(
	array *a, visit_func vistor, void *extra_data);

/**
 * Returns 1 if this array contains no elements, otherwise return 0
 */
int array_is_empty(const array *a);

/**
 * Returns the number of elements in this array
 */
int array_size(const array *a);

/**
 * Returns the number of elements that the array will contain now
 */
int array_capacity(const array *a);

/**
 * Init array_iterator, return 1 if success, otherwise return 0
 */
int array_iterator_init(array *a, array_iterator *it);

/**
 * Move iterator to next position
 * @return the next element in the iteration
 */
void* array_iterator_next(array_iterator *it);

/**
 * Get the element data which the current iterator point to
 */
void* array_iterator_elem(array_iterator *it);

/**
 * Returns 1 if the iteration has next element, otherwise return 0
 */
int array_iterator_has_next(const array_iterator *it);

/**
 * Removes element which the current iterator point to.
 */
void array_iterator_remove(array_iterator *it);

#endif
