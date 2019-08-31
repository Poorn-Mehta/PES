/*
 * custom_patternverify.c
 *
 *  Created on: Oct 31, 2018
 *      Author: poorn
 */


#include "custom_patternverify.h"


//add, len, seed, max

ptr_type *mem_ptr2, mem_i, *pattern_original;
float random_number, seed;
uint32_t max, range, random_value;
uint8_t verification_flag, verification_counter;
//clock_t t;

void gen_verify(void)
{
	random_number = ((0.4353491074*seed) + 0.8173946121);
	while(random_number > 1)
	{
		random_number /= 10;
	}
	random_number *= max;
	random_value = (uint32_t)random_number;
	output_string("\n\r%x\n\r", random_value);
	if(*mem_ptr2 == random_value)
	{
		verification_counter += 1;
	}
	seed = random_number;
}

void patternverify(void)
{
	verification_flag = 0;
	verification_counter = 0;
	if(mem_ptr)
	{
		range = value2;
		seed = (float) value3;
		max = value4;
		if(relative_address)
		{
			value1 = (value1 * 4) + (ptr_type)mem_ptr;
		}
		mem_ptr2 = (ptr_type *) value1;
		if(mem_ptr2)
		{
			pattern_original = mem_ptr2;
			Boundary_Check();
			if((boundary_error == 1) && (b_proceed == 0))
			{
				output_string("\n\rProcess Terminated\n\r");
			}
			else
			{
				value2 -= 1;
				value2 = (value2 * 4) + (ptr_type)pattern_original;
				mem_ptr2 = (ptr_type *) value2;
				Boundary_Check();
				if((boundary_error == 1) && (b_proceed == 0))
				{
					output_string("\n\rProcess Terminated\n\r");
				}
				else
				{
					mem_ptr2 = pattern_original;
					Detailed_Output();
					start_timing();
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
					while(seed > 1)
					{
						seed /= 10;
					}
					output_string("\n\rGenerated Psuedo Random Numbers: \n\r");
					uint8_t counter;
					for(counter = 0; counter < range; counter ++, mem_ptr2 ++)
					{
						gen_verify();
					}
					mem_ptr2 = pattern_original;
					if(verification_counter != range)
					{
						output_string("\n\rPattern Verification Failed\n\r");
					}
					else
					{
						output_string("\n\rPattern Verified Successfully\n\r");
					}
					stop_timing();
					output_string("\n\rThanks for verifying pattern...\n\r");
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
		output_string("\n\rUnfortunately, you have not been allocated any memory so far and so no memory write cannot be done...\n\r");
	}
}
