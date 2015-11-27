#include "mky_array.h"

typedef struct
{
	int data[10];
}Dog;

int main()
{
	int i = 0;
	Dog d;
	mky_array *a = mky_array_create(sizeof(Dog), NULL);
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		mky_array_add_last(a, &d);
	}
	mky_array_destroy(a);
	return 0;
}
