/*
 * Custom_ASCII_Counter.c
 *
 *  Created on: Nov 16, 2018
 *      Author: poorn
 */

#include "Custom_ASCII_Counter.h"
#include "Custom_UART.h"
#include "Custom_Circular_Buffer.h"

DWord Fib_n;

Byte Counter, ASCII_Char;
DWord ASCII_Array[256], ASCII_Value;
char UART_print[50];

//Function to set the array properly
void ASCII_Counter_Init(void)
{
	//Storing all ascii values in higher 8 bits
	for(Counter = 0; Counter < 0xFF; Counter ++)		ASCII_Array[Counter] = (Counter << 24);
	ASCII_Array[Counter] = (Counter << 24);
}

//Actual application
void ASCII_Counter(void)
{
	//Give out warning if overwriting
	if(CBuffer_Instance[UART0_Rx_Buffer_ID].Status == Full)		Output_String("\n\rOverwriting");

	//Read one byte
	CBuffer_Byte_Read(UART0_Rx_Buffer_ID, &ASCII_Char);

	//Scan for all valid ascii values
	for(Counter = 0; Counter < 0xFF; Counter ++)
	{
		//If match then increase the count by 1
		if((ASCII_Array[Counter] >> 24) == ASCII_Char)
		{
			ASCII_Value = ASCII_Array[Counter] & ASCII_Counter_Mask;
			ASCII_Value += 1;
			ASCII_Value &= ASCII_Counter_Mask;
			ASCII_Array[Counter] &= ASCII_Char_Mask;
			ASCII_Array[Counter] |= ASCII_Value;
			break;
		}
	}
	if(Counter == 0xFF)
	{
		ASCII_Value = ASCII_Array[Counter] & ASCII_Counter_Mask;
		ASCII_Value += 1;
		ASCII_Value &= ASCII_Counter_Mask;
		ASCII_Array[Counter] &= ASCII_Char_Mask;
		ASCII_Array[Counter] |= ASCII_Value;
	}

	//Printing fibonacci number
	sprintf(UART_print, "n\rFibonacci Number: %lu", Fib_n);
	Output_String(UART_print);

	//Printing report
	Output_String("\n\rNew Data\n\r");
	for(Counter = 0; Counter < 0xFF; Counter ++)
	{
		ASCII_Char = ASCII_Array[Counter] >> 24;
		ASCII_Value = ASCII_Array[Counter] & ASCII_Counter_Mask;
		if(ASCII_Value != 0)
		{
			sprintf(UART_print, "\n\rCharacter: %c\tHex: 0x%02X\tOccurrence: %ld", ASCII_Char, ASCII_Char, ASCII_Value);
			Output_String(UART_print);
		}
	}
	Output_String("\n\r\n\rEnter Text:\n\r");
}
