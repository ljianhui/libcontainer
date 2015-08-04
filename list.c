#include "list.h"

struct node
{
	struct node *prev;
	struct node *next;
	char elem[0];
};

struct list
{
	struct node *head;
	compare_func comparator;
	size_t elem_size;
	int size;
};

struct list_iterator
{
	struct list *lst;
	struct node *cur_node;
};
