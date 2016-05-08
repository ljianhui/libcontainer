#ifndef _C_LIBDEF_H
#define _C_LIBDEF_H

#include <stddef.h>

/**
 * typedef a function pointer that dump elem src to dst
 * @param dst point memory of dst object
 * @param src point memory of source object
 * @param size the bytes num of memory
 */
typedef void(*dump_func)(void *dst, const void *src, size_t size);

/**
 * release the resource alloc in dump_func
 */
typedef void(*release_func)(void *elem);

/**
 * typedef a function pointer
 * @return >0: x > y, == 0: x == y, <0: x < y
 */
typedef int(*compare_func)(const void *x, const void *y);

typedef struct c_elem_opt
{
	dump_func dump;
	release_func release;
	compare_func compare;
}c_elem_opt;

/**
 * typedef a function pointer
 * @return 0 continue to visit, not 0 stop visiting
 */
typedef int(*visit_func)(void *element, void *extra);

extern const void* C_ELEM_ZERO;

#endif

