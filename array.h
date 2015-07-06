#ifndef _ARRAY_H
#define _ARRAY_H

#include "libdef.h"

typedef struct array array;
typedef struct array_iterator array_iterator;

/**
 * Create a array
 * @param elem_size the size of element in the array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
array* create_array(size_t elem_size, compare_func comparator);

/**
 * Create a array with initial capacity, but size is zero
 * @param elem_size the size of element in the array
 * @param capacity the initial capacity of array
 * @param comparator the function pointer of int (*)(const void*, const void*)
 * @return array pointer, or NULL when error
 */
array* create_capacity_array(
	size_t elem_size, int capacity, compare_func comparator);

/**
 * Create a depth copy of this array instance.
 * @param src the source array
 * @return array pointer, or NULL when error
 */
array* clone_array(const array *src);

/**
 * Clear the array, after the operation, size == 0
 */
void clear_array(array *a);

/**
 * Destroy the array
 */
void destroy_array(array *a);

/**
 * Appends a depth copy of specified element to the end of this array
 * @return 1 if appends successfully, or 0 when failed 
 */
int append_to_array(array *a, const void *elem);

/**
 * Removes the last element of array
 * @return 1 if remove successfully, or 0 when failed
 */
int remove_last_from_array(array *a);

/**
 * Adds a depth copy specified element at the specified position in this array
 * After this operator the index of specified element is index
 * @return 1 if adds successfully, or 0 when failed
 */
int add_to_array(array *a, const void *elem, int index);

/**
 * Appends depth copy of all elements in the src array to the end of dst array
 * @return 1 if adds successfully, or 0 when failed
 */
int add_all_to_array(array *dst, const array *src);

/**
 * Removes the first occurrence of the specified element from this array
 * (Memory address or value of element equal to a element in the array)
 * @return 1 if adds successfully, or 0 when failed
 */
int remove_elem_from_array(array *a, const void *elem);

/**
 * Removes the element at the specified position in this array
 * @return 1 if adds successfully, or 0 when failed
 */
int remove_from_array(array *a, int index);

/**
 * Returns the element pointer at the specified position in this array
 */
void* get_from_array(const array *a, int index);

/**
 * Replaces the element at the specified position in this array
 * with a depth copy of specified element
 * @return 1 if set successfully, or 0 when failed
 */
int set_to_array(array *a, const void *elem, int index);

/**
 * Returns the index of the first occurrence of the specified element in this array,
 * or -1, if this array does not contain the element
 */
int index_of_array(const array *a, const void *elem);

/**
 * Visit each elements in the array. if visitor return not 0, it will stop visiting.
 * @param array will be visit
 * @param visitor the function pointer of int (*)(const void*, void*)
 *        if it return not 0, the operation will be stop
 * @extra_data save the result of visiting each elements
 */
void foreach_in_array(
	array *a, visit_func vistor, void *extra_data);

/**
 * Returns 1 if this array contains no elements, otherwise return 0
 */
int is_empty_array(const array *a);

/**
 * Returns the number of elements in this array
 */
int size_of_array(const array *a);

/**
 * Returns the number of elements that the array will contain now
 */
int capacity_of_array(const array *a);

/**
 * create the array_iterator, return the pointer of array_iterator
 */
array_iterator* create_array_iterator(array *a);

/**
 * Destroy the array_iterator
 */
void destroy_array_iterator(array_iterator *it);

/**
 * Move iterator to next position
 * @return the next element in the iteration
 */
void* next_array_iterator(array_iterator *it);

/**
 * Returns 1 if the iteration has next element, otherwise return 0
 */
int has_next_array_iterator(const array_iterator *it);

/**
 * Removes element which the current iterator point to.
 */
void remove_by_array_iterator(array_iterator *it);

#endif

