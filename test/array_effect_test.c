#include "array.h"

int compare(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

typedef struct
{
	int data[10];
}Dog;

int main()
{
	int i = 0;
	Dog d;
	array *a = create_array(sizeof(int), compare);
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		append_to_array(a, &d);
	}
	destroy_array(a);
	return 0;
}
