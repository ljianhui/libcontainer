#ifndef _c_STACK_H
#define _c_STACK_H

#include "c_libdef.h"

typedef struct c_deque c_stack;

c_stack* c_stack_create(size_t elem_size);
c_stack* c_stack_clone(const c_stack *src);
void c_stack_destroy(c_stack *s);

void* c_stack_push(c_stack *s, const void *elem);
void c_stack_pop(c_stack *s);
void* c_stack_top(const c_stack *s);
void c_stack_clear(c_stack *s);

int c_stack_is_empty(const c_stack *s);
int c_stack_size(const c_stack *s);

#endif
