#include <memory.h>
#include "c_array.h"

typedef struct
{
	int data[10];
}Dog;

void dog_dump(void *dst, const void *src, size_t size)
{
	memcpy(dst, src, size);
}

void dog_release(void *elem)
{
	return;
}

int dog_compare(const void *x, const void *y)
{
	return 0;
}

int main()
{
	int i = 0;
	Dog d;
	c_array *a = c_array_create(dog_dump, dog_release, dog_compare, sizeof(Dog));
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		c_array_add_last(a, &d);
	}
	c_array_destroy(a);
	return 0;
}
