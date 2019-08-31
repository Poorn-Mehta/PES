#include "Patternverify.h"

//add, len, seed, max

uint32_t *mem_ptr2, mem_i;
float random_number, seed;
uint32_t max, range, random_value, *pattern_original;
uint8_t verification_flag, verification_counter;
clock_t t;

void gen_verify(void)
{
	random_number = ((0.4353491074*seed) + 0.8173946121);
	while(random_number > 1)
	{
		random_number /= 10;
	}
	random_number *= max;
	random_value = (uint32_t)random_number;
	printf("\n%x", random_value);
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
			value1 = (value1 * 4) + (uint64_t)mem_ptr;
		}
		mem_ptr2 = (uint32_t *) value1;
		if(mem_ptr2)
		{
			pattern_original = mem_ptr2;
			Boundary_Check();
			if((boundary_error == 1) && (b_proceed == 0))
			{
				printf("\nProcess Terminated\n");
			}
			else
			{
				value2 -= 1;
				value2 = (value2 * 4) + (uint64_t)pattern_original;
				mem_ptr2 = (uint32_t *) value2;
				Boundary_Check();
				if((boundary_error == 1) && (b_proceed == 0))
				{
					printf("\nProcess Terminated\n");
				}
				else
				{
					mem_ptr2 = pattern_original;
					Detailed_Output();
					clkbegin();
					if(print)
					{
						printf("\nThe allocated addresses are as below:\n");
						for(mem_i = 0; mem_i < mem_max; mem_i ++, mem_ptr ++)
						{
							printf("\nRelative address: %d \t\t Actual address: %p \t\t Existing hex data at this location in Hex: %x\n", mem_i, mem_ptr, *mem_ptr);
						}
					}
					mem_ptr = mem_original;
					while(seed > 1)
					{
						seed /= 10;
					}
					printf("\nGenerated Psuedo Random Numbers: \n");
					uint8_t counter;
					for(counter = 0; counter < range; counter ++, mem_ptr2 ++)
					{
						gen_verify();
					}
					mem_ptr2 = pattern_original;
					if(verification_counter != range)
					{
						printf("\nPattern Verification Failed\n");
					}
					else
					{
						printf("\nPattern Verified Successfully\n");
					}
					clkend();
					printf("\nThanks for verifying pattern...\n");
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
		printf("\nUnfortunately, you have not been allocated any memory so far and so no memory write cannot be done...\n");
	}
}
