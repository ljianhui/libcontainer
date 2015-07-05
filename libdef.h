#ifndef _LIBDEF_H
#define _LIBDEF_H

/**
 * typedef a function pointer
 * @return >0: x > y, == 0: x == y, <0: x < y
 */
typedef int (*compare_func)(const void *x, const void *y);

/**
 * typedef a function pointer
 * @return 0 continue to visit, not 0 stop visiting
 */
typedef int (*visit_func)(void *element, void *extra);

#endif

