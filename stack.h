#ifndef _STACK_H
#define _STACK_H

#include "libdef.h"

typedef struct deque stack;

stack* stack_create(size_t elem_size);
stack* stack_clone(const stack *src);
void stack_destroy(stack *s);

void* stack_push(stack *s, const void *elem);
void stack_pop(stack *s);
void* stack_top(const stack *s);
void stack_clear(stack *s);

int stack_is_empty(const stack *s);
int stack_size(const stack *s);

#endif
