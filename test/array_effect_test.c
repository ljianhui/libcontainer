#include "array.h"

typedef struct
{
	int data[10];
}Dog;

int main()
{
	int i = 0;
	Dog d;
	array *a = create_array(sizeof(Dog), NULL);
	for (i = 0; i < 1 * 1024 * 1024; ++i)
	{
		append_to_array(a, &d);
	}
	destroy_array(a);
	return 0;
}
