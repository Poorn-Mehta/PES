/*
 * custom_main.c
 *
 *  Created on: Oct 29, 2018
 *      Author: poorn
 */

#include "custom_main.h"
#include "custom_help.h"
#include "custom_input.h"

char input[250], input1[50], input2[50], input3[50], input4[50], input5[50];
uint8_t main_i, main_j, exit_flag, space_flag, relative_address;

char m_print[50];
uint8_t print = 0;

clock_t t;

char b_input[50];
uint8_t b_proceed = 0;
uint8_t boundary_error = 0;

#ifdef	FRDM
void FGETS(char *array_to_write, uint8_t bytes, FILE *stream)
{
	char *tmp;
	tmp = array_to_write;
	do{
		*array_to_write = GETCHAR();
		PUTCHAR(*array_to_write);
		if(*array_to_write == Enter_Detected)	break;
		array_to_write += 1;
	}while(array_to_write < (tmp + bytes));
}

void Timer_Config(void)
{
    // LPTMR configurations
    lptmr_user_config_t lptmrConfig =
    {
        .timerMode = kLptmrTimerModeTimeCounter,
        .freeRunningEnable = true,
        .prescalerEnable = false,
        .prescalerClockSource = kClockLptmrSrcMcgIrClk,//kClockLptmrSrcLpoClk
        .prescalerValue = kLptmrPrescalerDivide2,//kLptmrPrescalerDivide4GlitchFilter2
        .isInterruptEnabled = false,//true
    };
    // LPTMR driver state information
    lptmr_state_t lptmrState;

    // Initialize LPTMR
    LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);
}

void Timer_Start(void)
{
	LPTMR_DRV_Start(LPTMR0_IDX);
}

void Timer_Stop(void)
{
	//    LPTMR_Type *abc = g_lptmrBase[LPTMR0_IDX];
	//    val123 = LPTMR_HAL_GetCounterValue(abc);
//	uint32_t ttt;
//	for(ttt = 0; ttt < 1000; ttt ++);
    uint32_t time_taken;
    time_taken = LPTMR_DRV_GetCurrentTimeUs(LPTMR0_IDX);
    LPTMR_DRV_Stop(LPTMR0_IDX);
	output_string("\n\rThe process took %d micro seconds to execute\n\r", time_taken);
}
#endif

#ifdef	HOST
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
#endif

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
			output_string("\n\rProvided memory location is outside of allocated space\n\r\n\rProceeding anyway can be dangerous\n\r");
#ifdef FRDM
			output_string("\n\rMemory address that you're trying to access: %x\n\r",mem_ptr2);
			output_string("\n\rHighest memory address that is allocated: %x\n\r",(mem_original + (mem_max - 1)));
#else
			output_string("\n\rMemory address that you're trying to access: %p\n\r",mem_ptr2);
			output_string("\n\rHighest memory address that is allocated: %p\n\r",(mem_original + (mem_max - 1)));
#endif
			output_string("\n\r Type Y or y to avoid the warning and proceed,\n\ror type N or n to abort the operation: ");
			input_string(b_input, 50, stdin);
			output_string("\n\r");
			if((b_input[1] == 0) || (b_input[1] == Enter_Detected))
			{
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
				else	output_string("\n\rInvalid Input, Try again\n\r");
			}
			else	output_string("\n\rInvalid Input, Try again\n\r");
		}
	}
}

void Detailed_Output(void)
{
	while(1)
	{
		output_string("\n\rDo you want to use Detailed information?\n\r");
		output_string("\n\r Type Y or y to accept, type N or n to reject: ");
		input_string(m_print, 50, stdin);
		output_string("\n\r");
		if((m_print[1] == 0) || (m_print[1] == Enter_Detected))
		{
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
			else	output_string("\n\rInvalid Input, Try again\n\r");
		}
		else	output_string("\n\rInvalid Input, Try again\n\r");
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

void cmain(void)
{
	output_string("\n\rWelcome\n\rThis Project is developed by\n\rPoorn Mehta & Rushi Macwan\n\r");
	relative_address = 1;
	Array_Cleanup(input);
	Array_Cleanup(input1);
	Array_Cleanup(input2);
	Array_Cleanup(input3);
	Array_Cleanup(input4);
	Array_Cleanup(input5);
	Help_Init();
	Input_Init();
#ifdef FRDM
	Timer_Config();
#endif
	char address_type[50];
	while(1)
	{
		output_string("\n\rDo you want to use Relative/Easy Addressing?\n");
		output_string("\n\rType Y or y to accept or\n\rtype N or n to reject\n\rand use absolute/direct addressing: ");
		input_string(address_type, 50, stdin);
		if((address_type[1] == 0) || (address_type[1] == Enter_Detected))
		{
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
			else	output_string("\n\n\rInvalid Input, Try again\n");
		}
		else	output_string("\n\n\rInvalid Input, Try again\n");
	}
	output_string("\n\rRelative Addressing Value set to: %d\n", relative_address);
	while(1)
	{
		exit_flag = 0;
		space_flag = 0;
		output_string("\n\rEnter Command: ");
		input_string(input, 250, stdin);
		main_i = 0;
		while(input[main_i] != Enter_Detected)
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
#ifdef	FRDM	
				output_string("\n\n\rExit From Code\n\n\rGoing into Infinite Loop\n\r");
				while(1);
#else
				break;			
#endif			
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

