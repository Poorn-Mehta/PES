/*
 * custom_main.h
 *
 *  Created on: Oct 29, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_MAIN_H_
#define CUSTOM_MAIN_H_

#if defined(TWR_KV46F150M)
#define LPTMR0_IDX LPTMR_IDX
#endif

#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
//#ifdef	HOST

//#endif

#include "custom_system_identifier.h"

#ifdef	FRDM
#include "MKL25Z4.h"
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include "fsl_os_abstraction_bm.h"
#endif

#define Invalid()	output_string("\nInvalid Command\n")
#define Null_Ptr()	output_string("\nNull Pointer. Can't proceed. Abort.\n")



typedef volatile uint8_t vuint8_t;
typedef volatile uint32_t	vuint32_t;

extern char input[250], input1[50], input2[50], input3[50], input4[50], input5[50];
extern uint8_t main_i, main_j, exit_flag, space_flag, relative_address, getc_i;
extern ptr_type value, value1, value2, value3, value4;

extern char m_print[50];
extern uint8_t print;

extern uint8_t boundary_error;
extern char b_input[50];
extern uint8_t b_proceed;

#ifdef HOST
extern clock_t t;
#endif

extern ptr_type *mem_ptr, *mem_ptr2, *mem_original, mem_max;

#ifdef	FRDM
void FGETS(char *array_to_write, uint8_t bytes, FILE *stream);
#endif

void Array_Cleanup(char *clean_ptr);
void Detailed_Output(void);

#ifdef	FRDM
void Timer_Config(void);
void Timer_Start(void);
void Timer_Stop(void);
#else
void clkbegin(void);
void clkend(void);
#endif

void Boundary_Check(void);
void cmain(void);

#endif /* CUSTOM_MAIN_H_ */
