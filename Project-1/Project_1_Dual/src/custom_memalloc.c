/*
 * custom_memalloc.c
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */


#include "custom_memalloc.h"

ptr_type *mem_ptr, *mem_original, mac_i, mem_max;

void memalloc(void)
{
	mem_max = value1;
	mem_ptr = (ptr_type*) malloc (value1);
	if(mem_ptr)
	{
		mem_original = mem_ptr;
		Detailed_Output();
		if(print)
		{
			output_string("\n\rThe allocated addresses are as below:\n\r");
			for(mac_i = 0; mac_i < mem_max; mac_i ++, mem_ptr ++)
			{
#ifdef FRDM
				output_string("\n\rRelative address: %d \t\t Actual address: %x\n\rExisting hex data at this location in Hex: %x\n\r\n\r", mac_i, mem_ptr, *mem_ptr);
#else
				output_string("\n\rRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n\r\n\r", mac_i, mem_ptr, *mem_ptr);
#endif
			}
		}
		mem_ptr = mem_original;
		output_string("\n\r\n\rThanks for executing the memory allocation operation...\n\r");
	}
	else	output_string("\n\rMalloc Returned with Error\n\r");
}
