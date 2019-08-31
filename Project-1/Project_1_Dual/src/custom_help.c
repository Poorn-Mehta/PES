/*
 * custom_help.c
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */

#include "custom_help.h"

const char h[] = "help";
const char hd[] = "\n\n\r\rDirections to use help command:\n\rPut a whitespace after help and then type the command\n\rTo get information on using that command\n\rFor example - type: help exit\n\r\n\rList of valid Commands:\n\r";
const char h1[] = "exit";
const char h2[] = "memalloc";
const char h3[] = "memfree";
const char h4[] = "memwrite";
const char h5[] = "memread";
const char h6[] = "meminv";
const char h7[] = "patterngen";
const char h8[] = "patternverify";
const char hre[] = "\n\rCommand not recognized\n\r";
const char hr1[] = "\n\rexit: \n\rType exit to close the program\n\r";
const char hr2[] = "\n\rMemory Allocation:\n\r\n\rType memalloc and then enter the\n\rnumber of memory locations that you want\n\rto use and have access to.\n\r\n\rAlternatively, type memalloc <number> without <> for value\n\r";
const char hr3[] = "\n\rMemory Free:\n\rType memfree to release the \n\rpreviously allocated memory locations\n\r";
const char hr4[] = "\n\rMemory Write:\n\rType memwrite and then enter the address and data\n\rto write 32bit data at memory location of your choice.\n\r\n\rAlternatively, type memwrite <address> <data> without <> for values\n\r";
const char hr5[] = "\n\rMemory Read:\n\rType memread to read 32bit data in hex\n\rat memory location of your choice.\n\r\n\rAlternatively, type memread <address> without <> for value\n\r";
const char hr6[] = "\n\rMemory Inverse:\n\rType meminv to invert all bits of a\n\r32bit memory block at location of your choice\n\r";
const char hr7[] = "\n\rPsuedo Random Pattern Generation:\n\rType patterngen and then enter maximum value,\n\rseed, number of 32bits words that you wish to generate,\n\rand starting memory location to store the pattern\n\rto generate multiple psuedo random numbers.\n\r\n\rAlternatively, type patterngen <starting memory address> <length of pattern> <seed> <maxvalue>\n\rwithout <> for values\n\r";
const char hr8[] = "\n\rPsuedo Random Pattern Verification:\n\rType patternverify and then enter maximum value,\n\rseed, number of 32bits words that you wish to verify,\n\rand starting memory location pointing to the stored pattern\n\rto verify multiple psuedo random numbers.\n\r\n\rAlternatively, type patternverify <starting memory address> <length of pattern> <seed> <maxvalue>\n\rwithout <> for values\n\r";


char help_print[500], help_array[500];
uint8_t help_i, help_j, help_k;

void (*Help_Func_Ptr[8]) (void) =
								{
									Help_Response1,
									Help_Response2,
									Help_Response3,
									Help_Response4,
									Help_Response5,
									Help_Response6,
									Help_Response7,
									Help_Response8
								};

void Help_Response1(void)
{
	output_string("%s",hr1);
}

void Help_Response2(void)
{
	output_string("%s",hr2);
}

void Help_Response3(void)
{
	output_string("%s",hr3);
}

void Help_Response4(void)
{
	output_string("%s",hr4);
}

void Help_Response5(void)
{
	output_string("%s",hr5);
}
void Help_Response6(void)
{
	output_string("%s",hr6);
}

void Help_Response7(void)
{
	output_string("%s",hr7);
}

void Help_Response8(void)
{
	output_string("%s",hr8);
}

void Help_Init(void)
{
	help_j = 0;
	help_k = 0;
	while(h1[help_k] != 0)
	{
		help_array[help_j] = h1[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h2[help_k] != 0)
	{
		help_array[help_j] = h2[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h3[help_k] != 0)
	{
		help_array[help_j] = h3[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h4[help_k] != 0)
	{
		help_array[help_j] = h4[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h5[help_k] != 0)
	{
		help_array[help_j] = h5[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h6[help_k] != 0)
	{
		help_array[help_j] = h6[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h7[help_k] != 0)
	{
		help_array[help_j] = h7[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
	help_j += 1;
	help_k = 0;
	while(h8[help_k] != 0)
	{
		help_array[help_j] = h8[help_k];
		help_j += 1;
		help_k += 1;
	}
	help_array[help_j] = 0;
}

void Help_Display(void)
{
	output_string("%s",hd);
	output_string("\n\r\t%s",h);
	output_string("\n\r\t%s",h1);
	output_string("\n\r\t%s",h2);
	output_string("\n\r\t%s",h3);
	output_string("\n\r\t%s",h4);
	output_string("\n\r\t%s",h5);
	output_string("\n\r\t%s",h6);
	output_string("\n\r\t%s",h7);
	output_string("\n\r\t%s",h8);
	output_string("\n\r");
}

void Help_Lookup(void)
{
	help_i = 0;
	for(help_k = 0; help_k < Number_of_Help_Functions; help_k ++)//Number_of_Help_Functions
	{
		help_j = 0;
		while((help_array[help_i] != 0) && (input2[help_j] != 0))
		{
			if(help_array[help_i] == input2[help_j])
			{
				help_j += 1;
				help_i += 1;
			}
			else
			{
				break;
			}
		}
		if((help_array[help_i] == 0) && (input2[help_j] == 0))
		{
			(*Help_Func_Ptr[help_k])();
			break;
		}
		else
		{
			while(help_array[help_i] != 0)
			{
				help_i += 1;
			}
			if(help_k == (Number_of_Help_Functions - 1))
			{
				output_string("%s",hre);
			}
		}
		help_i += 1;
	}
}
