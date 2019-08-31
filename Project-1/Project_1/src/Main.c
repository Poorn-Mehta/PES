#include "Main.h"
#include "Help.h"
#include "Input.h"

#define TARGET_DEVICE (__linux__ || _WIN64 || __APPLE__ )
#if TARGET_DEVICE
    #define HOST
#else
    #define FRDM
#endif

char input[250], input1[50], input2[50], input3[50], input4[50], input5[50];
uint8_t main_i, main_j, exit_flag, space_flag, relative_address;

char m_print[50];
uint8_t print = 0;

clock_t t;

char b_input[50];
uint8_t b_proceed = 0;
uint8_t boundary_error = 0;

void clkbegin(void)
{ 
    t = clock(); 
}

void clkend(void)
{
	t = clock() - t; 
    double time_taken = (((double)t)/CLOCKS_PER_SEC) * 1000; // in milli seconds 
	printf("\nThe process took %f milli seconds to execute\n", time_taken); 
}

void Boundary_Check(void)
{
	if((mem_ptr2 >= mem_original) && (mem_ptr2 <= (mem_original + (mem_max - 1))))
	{
		boundary_error = 0;
	}
	else
	{
		boundary_error = 1;
		while(1)
		{
			printf("\nProvided memory location is outside of allocated space\n\nProceeding anyway can be dangerous\n");
			printf("\nMemory address that you're trying to access: %p\n",mem_ptr2);
			printf("\nHighest memory address that is allocated: %p\n",(mem_original + (mem_max - 1)));
			printf("\n Type Y or y to avoid the warning and proceed,\nor type N or n to abort the operation: ");
			fgets(b_input, 50, stdin);
			printf("\n");
			if((b_input[0] == 'Y') || (b_input[0] == 'y'))
			{
				b_proceed = 1;
				break;
			}
			else if((b_input[0] == 'N') || (b_input[0] == 'n'))
			{
				b_proceed = 0;
				break;
			}
			else
			{
				printf("\nInvalid Input, Try again\n");
			}
		}
	}
}

void Detailed_Output(void)
{
	while(1)
	{
		printf("\nDo you want to use Detailed information?\n");
		printf("\n Type Y or y to accept, type N or n to reject: ");
		fgets(m_print, 50, stdin);
		printf("\n");
		if((m_print[0] == 'Y') || (m_print[0] == 'y'))
		{
			print = 1;
			break;
		}
		else if((m_print[0] == 'N') || (m_print[0] == 'n'))
		{
			print = 0;
			break;
		}
		else
		{
			printf("\nInvalid Input, Try again\n");
		}
	}
}

void Array_Cleanup(char *clean_ptr)
{
	if(clean_ptr)
	{
		while(*clean_ptr != 0)
		{
			*clean_ptr = 0;
			clean_ptr += 1;
		}
	}
	else
	{
		Null_Ptr();
	}
}

int main(void)	
{
	#ifdef	HOST
	printf("\nHost System\n");
	#endif
	relative_address = 1;
	Array_Cleanup(input);
	Array_Cleanup(input1);
	Array_Cleanup(input2);
	Array_Cleanup(input3);
	Array_Cleanup(input4);
	Array_Cleanup(input5);
	Help_Init();
	Input_Init();
	char address_type[50];
	while(1)
	{
		printf("Do you want to use Relative/Easy Addressing?\n");
		printf("\n Type Y or y to accept, type N or n to reject\nand use absolute/direct addressing: ");
		fgets(address_type, 50, stdin);
		if((address_type[0] == 'Y') || (address_type[0] == 'y'))
		{
			relative_address = 1;
			break;
		}
		else if((address_type[0] == 'N') || (address_type[0] == 'n'))
		{
			relative_address = 0;
			break;
		}
		else
		{
			printf("\nInvalid Input, Try again\n");
		}
	}
	printf("\nRelative Addressing Value set to: %d\n", relative_address);
	while(1)
	{
		exit_flag = 0;
		space_flag = 0;
		printf("\nEnter Command: ");
		fgets(input, 250, stdin);
		main_i = 0;
		while(input[main_i] != '\n')
		{
			main_i += 1;
		}
		input[main_i] = 0;
		main_i = 0;
		while((input[main_i] != 0) && (input[main_i] != ' '))
		{
			input1[main_i] = input[main_i];
			main_i += 1;
		}
		main_j = 0;
		while(input[main_i] != 0)
		{
			if(input[main_i] == ' ')
			{
				space_flag += 1;
				main_i += 1;
				while((input[main_i] != ' ') && (input[main_i] != 0))
				{
					input2[main_j] = input[main_i];
					main_i += 1;
					main_j += 1;
				}
				if(input[main_i] == ' ')
				{
					space_flag += 1;
					main_j = 0;
					main_i += 1;
					while((input[main_i] != ' ') && (input[main_i] != 0))
					{
						input3[main_j] = input[main_i];
						main_i += 1;
						main_j += 1;
					}
					if(input[main_i] == ' ')
					{
						space_flag += 1;
						main_j = 0;
						main_i += 1;
						while((input[main_i] != ' ') && (input[main_i] != 0))
						{
							input4[main_j] = input[main_i];
							main_i += 1;
							main_j += 1;
						}
						if(input[main_i] == ' ')
						{
							space_flag += 1;
							main_j = 0;
							main_i += 1;
							while((input[main_i] != ' ') && (input[main_i] != 0))
							{
								input5[main_j] = input[main_i];
								main_i += 1;
								main_j += 1;
							}	
						}			
					}
				}
			}
			main_i += 1;
		}
		main_i = 0;
		main_j = 0;
		if(input[main_i] != 0)
		{
			Input_Lookup();
			if(exit_flag)
			{
				return 0;
			}	
		}
		Array_Cleanup(input);
		Array_Cleanup(input1);
		Array_Cleanup(input2);
		Array_Cleanup(input3);
		Array_Cleanup(input4);
		Array_Cleanup(input5);
	}
}
