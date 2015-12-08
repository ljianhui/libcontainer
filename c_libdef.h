#ifndef _C_LIBDEF_H
#define _C_LIBDEF_H

#include <stddef.h>

/**
 * typedef a function pointer
 * @return >0: x > y, == 0: x == y, <0: x < y
 */
typedef int(*compare_func)(const void *x, const void *y);

/**
 * typedef a function pointer
 * @return 0 continue to visit, not 0 stop visiting
 */
typedef int(*visit_func)(void *element, void *extra);

static const int C_INT_ZERO = 0;
static const void* C_ELEM_ZERO = (const void*)&C_INT_ZERO;

#endif

