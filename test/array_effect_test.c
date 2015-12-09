#include "c_array.h"

typedef struct
{
	int data[10];
}Dog;

int main()
{
	int i = 0;
	Dog d;
	c_array *a = c_array_create(sizeof(Dog), NULL);
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		c_array_add_last(a, &d);
	}
	c_array_destroy(a);
	return 0;
}
