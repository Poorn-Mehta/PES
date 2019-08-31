#include "Memfree.h"

void memfree(void)
{
	if(mem_ptr)
	{
		free(mem_ptr);
		printf("\nThe allocated memory has been successfully freed...\n");
		printf("\nThanks for freeing the allocated memory...\n");
	}
	else
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so no memory was freed...\n");
	}
}
