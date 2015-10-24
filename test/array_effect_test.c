#include "array.h"

typedef struct
{
	int data[10];
}Dog;

int main()
{
	int i = 0;
	Dog d;
	array *a = array_create(sizeof(Dog), NULL);
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		array_add_last(a, &d);
	}
	array_destroy(a);
	return 0;
}
