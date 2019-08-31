/*
 * custom_memwrite.c
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */

#include "custom_memwrite.h"

ptr_type *mem_ptr2, mem_i;

void memwrite(void)
{
	if(mem_ptr)
	{
		if(relative_address)
		{
			value1 = (value1 * 4) + (ptr_type)mem_ptr;
		}
		mem_ptr2 = (ptr_type *) value1;
		if(mem_ptr2)
		{
			Boundary_Check();
			if((boundary_error == 1) && (b_proceed == 0))
			{
				output_string("\n\rProcess Terminated\n\r");
			}
			else
			{
				Detailed_Output();
				if(print)
				{
					output_string("\n\rInformation BEFORE write operation\n\r\n\r");
					output_string("\n\rThe allocated addresses are as below:\n\r");
					for(mem_i = 0; mem_i < mem_max; mem_i ++, mem_ptr ++)
					{
#ifdef FRDM
						output_string("\n\rRelative address: %d \t\t Actual address: %x\n\rExisting hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#else
						output_string("\n\rRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#endif
					}
				}
				mem_ptr = mem_original;
				if(print == 0)
				{
#ifdef FRDM
					output_string("\n\rThe hex data at the specified location BEFORE writing, at %x is %x\n\r", mem_ptr2, *mem_ptr2);
#else
					output_string("\n\rThe hex data at the specified location BEFORE writing, at %p is %x\n\r", mem_ptr2, *mem_ptr2);
#endif
				}

				*mem_ptr2 = value2;

				if(print == 0)
				{
#ifdef FRDM
					output_string("\n\rThe hex data at the specified location AFTER writing, at %x is %x\n\r", mem_ptr2, *mem_ptr2);
#else
					output_string("\n\rThe hex data at the specified location AFTER writing, at %p is %x\n\r", mem_ptr2, *mem_ptr2);
#endif
				}
				else
				{
					output_string("\n\rInformation AFTER write operation\n\r\n\r");
					output_string("\n\rThe allocated addresses are as below:\n\r");
					for(mem_i = 0; mem_i < mem_max; mem_i ++, mem_ptr ++)
					{
#ifdef FRDM
						output_string("\n\rRelative address: %d \t\t Actual address: %x\n\rExisting hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#else
						output_string("\n\rRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#endif
					}
				}
				mem_ptr = mem_original;
				output_string("\n\rThanks for writing to an allocated memory location...\n\r");
			}
		}
		else
		{
			Null_Ptr();
		}
	}
	else
	{
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so no memory write cannot be done...\n\r");
	}
}
