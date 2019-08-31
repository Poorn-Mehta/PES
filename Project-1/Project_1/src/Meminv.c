#include "Meminv.h"

uint32_t *mem_ptr2, mem_i;

clock_t t;

void meminv(void)
{
	if(mem_ptr)
	{
		mem_ptr = mem_original;
		if(relative_address)
		{
			value1 = (value1 * 4) + (uint64_t)mem_ptr;
		}
		mem_ptr2 = (uint32_t *) value1;
		if(mem_ptr2)
		{
			Boundary_Check();
			if((boundary_error == 1) && (b_proceed == 0))
			{
				printf("\nProcess Terminated\n");
			}
			else
			{
				Detailed_Output();
				if(print)
				{
					printf("\nInformation BEFORE Inverting operation\n\n");
					printf("\nThe allocated addresses are as below:\n");
					for(mem_i = 0; mem_i < mem_max; mem_i ++, mem_ptr ++)
					{
						printf("\nRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n", mem_i, mem_ptr, *mem_ptr);
					}
				}
				mem_ptr = mem_original;
				if(print == 0)
				{
					printf("\nThe data in hex at the specified memory location BEFORE Inverting is %x\n", *mem_ptr2);
				}
				clkbegin();
				*mem_ptr2 ^= 0xFFFFFFFF;
				clkend();
				if(print == 0)
				{
					printf("\nThe data in hex at the specified memory location AFTER Inverting is %x\n", *mem_ptr2);
				}
				else
				{
					printf("\nInformation AFTER Inverting operation\n\n");
					printf("\nThe allocated addresses are as below:\n");
					for(mem_i = 0; mem_i < mem_max; mem_i ++, mem_ptr ++)
					{
						printf("\nRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n", mem_i, mem_ptr, *mem_ptr);
					}
				}
				mem_ptr = mem_original;
				printf("\nThanks for performing an XOR operation at an allocated memory location...\n");
			}
		}
		else
		{
			Null_Ptr();
		}
	}
	else
	{
		printf("\nUnfortunately, you have not been allocated any memory so far and so XORing is not possible at this moment...\n");
	}
}
