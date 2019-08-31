/*
 * custom_memfree.c
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */

#include "custom_memfree.h"

void memfree(void)
{
	if(mem_ptr)
	{
		free(mem_ptr);
		output_string("\n\rThe allocated memory has been successfully freed...\n\r");
		output_string("\n\rThanks for freeing the allocated memory...\n\r");
	}
	else
	{
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so no memory was freed...\n\r");
	}
}
