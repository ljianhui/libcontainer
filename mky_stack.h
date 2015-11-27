#ifndef _MKY_STACK_H
#define _MKY_STACK_H

#include "mky_libdef.h"

typedef struct mky_deque mky_stack;

mky_stack* mky_stack_create(size_t elem_size);
mky_stack* mky_stack_clone(const mky_stack *src);
void mky_stack_destroy(mky_stack *s);

void* mky_stack_push(mky_stack *s, const void *elem);
void mky_stack_pop(mky_stack *s);
void* mky_stack_top(const mky_stack *s);
void mky_stack_clear(mky_stack *s);

int mky_stack_is_empty(const mky_stack *s);
int mky_stack_size(const mky_stack *s);

#endif
