/*
 * Custom_ASCII_Counter.h
 *
 *  Created on: Nov 16, 2018
 *      Author: Poorn Mehta and Rushi James Macwan
 */

#ifndef CUSTOM_INCLUDES_CUSTOM_ASCII_COUNTER_H_
#define CUSTOM_INCLUDES_CUSTOM_ASCII_COUNTER_H_

#include "Custom_Main.h"

//A single 32bit array is used for both - to store all ascii values and to store counts of them
//Each double word will have both. MSB 8 bits holding ascii char and lower 24 bits holding counts
#define ASCII_Char_Mask			0xFF000000
#define ASCII_Counter_Mask		0x00FFFFFF

extern Byte Counter, ASCII_Char;
extern DWord ASCII_Array[256], ASCII_Value;

void ASCII_Counter_Init(void);
void ASCII_Counter(void);

#endif /* CUSTOM_INCLUDES_CUSTOM_ASCII_COUNTER_H_ */
