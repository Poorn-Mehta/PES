#include "Memalloc.h"

uint32_t *mem_ptr, mac_i, mem_max, *mem_original;

void mem_clear(void)
{
	for(mac_i = 0; mac_i < value1; mac_i ++)
	{
		*mem_ptr = 0x00000000;
	}
}

void memalloc(void)
{
	mem_max = value1;
	mem_ptr = (uint32_t *) malloc (value1);
	mem_original = mem_ptr;
	mem_clear();
	Detailed_Output();
	if(print)
	{
		printf("\nThe allocated addresses are as below:\n");
		for(mac_i = 0; mac_i < mem_max; mac_i ++, mem_ptr ++)
		{
			printf("\nRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n", mac_i, mem_ptr, *mem_ptr);
		}
	}
	mem_ptr = mem_original;
	printf("\n\nThanks for executing the memory allocation operation...\n");	
}
