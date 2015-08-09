#ifndef _LIST_H
#define _LIST_H

#include "libdef.h"

typedef struct list list;
typedef struct list_iterator list_iterator;

list* create_list(size_t elem_size, compare_func comparator);
list* clone_list(const list *src);

void clear_list(list *lst);
void destroy_list(list *lst);

int add_first_to_list(list *lst, const void *elem);
int append_to_list(list *lst, const void *elem);
int add_to_list(list *lst, const void *elem, int index);
int add_all_to_list(list *dst, const list *src);

int remove_first_from_list(list *lst);
int remove_last_from_list(list *lst);
int remove_from_list(list *lst, int index);

void* get_first_of_list(const list *lst);
void* get_last_of_list(const list *lst);
void* get_from_list(const list *lst, int index);

void* set_first_of_list(list *lst, const void *elem);
void* set_last_of_list(list *lst, const void *elem);
void* set_to_list(list *lst, const void *elem, int index);

void foreach_in_list(list *lst, visit_func vistor, void *extra_data);

int size_of_list(const list *lst);
int is_empty_list(const list *lst);

list_iterator get_list_iterator(list *lst);
void destroy_list_iterator(list_iterator *lst);
void* next_list_iterator(list_iterator *it);
int has_next_list_iterator(const list_iterator *it);
void remove_by_list_iterator(list_iterator *it);
void add_by_list_iterator(list_iterator *it);

#endif

