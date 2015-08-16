#ifndef _LIST_H
#define _LIST_H

#include "libdef.h"

struct list_iterator
{
	struct list *lst;
	struct node *cur_node;
};
typedef struct list_iterator list_iterator;

typedef struct list list;

list* list_create(size_t elem_size, compare_func comparator);
list* list_clone(const list *src);

void list_clear(list *lst);
void list_destroy(list *lst);

int list_add_first(list *lst, const void *elem);
int list_append(list *lst, const void *elem);
int list_add(list *lst, const void *elem, int index);
int list_add_all(list *dst, const list *src);

int list_remove_first(list *lst);
int list_remove_last(list *lst);
int list_remove_elem(list *lst, const void *elem);
int list_remove(list *lst, int index);

void* list_get_first(const list *lst);
void* list_get_last(const list *lst);
void* list_get(const list *lst, int index);

void list_set_first(list *lst, const void *elem);
void list_set_last(list *lst, const void *elem);
void list_set(list *lst, const void *elem, int index);

void list_foreach(list *lst, visit_func vistor, void *extra_data);
int list_find(const list *lst, const void *elem, list_iterator *it);

int list_size(const list *lst);
int list_is_empty(const list *lst);

int list_iterator_init(list *lst, list_iterator *it);
void* list_iterator_next(list_iterator *it);
void* list_iterator_elem(const list_iterator *it);
int list_iterator_has_next(const list_iterator *it);
void list_iterator_remove(list_iterator *it);
void list_iterator_add(list_iterator *it, const void *elem);

#endif
