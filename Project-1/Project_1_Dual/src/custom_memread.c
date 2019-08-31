/*
 * custom_memread.c
 *
 *  Created on: Oct 31, 2018
 *      Author: poorn
 */

#include "custom_memread.h"

ptr_type *mem_ptr2, mem_i;

void memread(void)
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
				output_string("\n\rThe hex data at the specified location %x is %x\n\r", mem_ptr2, *mem_ptr2);
				output_string("\n\rThanks for reading from an allocated memory location...\n\r");
			}
		}
		else
		{
			Null_Ptr();
		}
	}
	else
	{
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so no memory can be read...\n\r");
	}
}

void memread_m(void)
{
	if(mem_ptr)
	{
		if(relative_address)
		{
			value2 = (value2 * 4) + (ptr_type)mem_ptr;
		}
		mem_ptr2 = (ptr_type *) value2;
		ptr_type *mem_tmp;
		mem_tmp = mem_ptr2;
		if(mem_ptr2)
		{
			Boundary_Check();
			if((boundary_error == 1) && (b_proceed == 0))
			{
				output_string("\n\rProcess Terminated\n\r");
			}
			else
			{
				value1 -= 1;
				value1 = (value1 * 4) + (ptr_type)mem_ptr2;
				mem_ptr2 = (ptr_type *) value1;
				Boundary_Check();
				if((boundary_error == 1) && (b_proceed == 0))
				{
					output_string("\n\rProcess Terminated\n\r");
				}
				else
				{
					ptr_type mem_init = (ptr_type)(mem_tmp - mem_original);
					for(mem_i = mem_init; mem_i <= (((ptr_type)(mem_ptr2 - mem_tmp)) + mem_init); mem_i ++, mem_ptr ++)
					{
#ifdef FRDM
						output_string("\n\rRelative address: %d \t\t Actual address: %x\n\rExisting hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#else
						output_string("\n\rRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n\r", mem_i, mem_ptr, *mem_ptr);
#endif
					}
					mem_ptr = mem_original;
					output_string("\n\rThanks for reading from an allocated memory location...\n\r");
				}
			}
		}
		else
		{
			Null_Ptr();
		}
	}
	else
	{
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so no memory can be read...\n\r");
	}
}
