/*
 * custom_meminv.c
 *
 *  Created on: Oct 31, 2018
 *      Author: poorn
 */


#include "custom_meminv.h"

ptr_type *mem_ptr2, mem_i;

#ifdef HOST
clock_t t;
#endif

void meminv(void)
{
	if(mem_ptr)
	{
		mem_ptr = mem_original;
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
					output_string("\n\rInformation BEFORE Inverting operation\n\r\n\r");
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
					output_string("\n\rThe data in hex at the specified memory location BEFORE Inverting is %x\n\r", *mem_ptr2);
				}
				start_timing();
				*mem_ptr2 ^= 0xFFFFFFFF;
				stop_timing();
				if(print == 0)
				{
					output_string("\n\rThe data in hex at the specified memory location AFTER Inverting is %x\n\r", *mem_ptr2);
				}
				else
				{
					output_string("\n\rInformation AFTER Inverting operation\n\r\n\r");
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
				output_string("\n\rThanks for performing an XOR operation at an allocated memory location...\n\r");
			}
		}
		else
		{
			Null_Ptr();
		}
	}
	else
	{
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so XORing is not possible at this moment...\n\r");
	}
}
