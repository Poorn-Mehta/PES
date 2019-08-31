/*
 * custom_main.h
 *
 *  Created on: Oct 29, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_MAIN_H_
#define CUSTOM_MAIN_H_


#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define PROJECT_3		1

#include "Custom_Sys_Identifier.h"

#ifdef	FRDM
//#include "core_cm0plus.h"
#include "MKL25Z4.h"
//#include "board.h"
#include "fsl_debug_console.h"
//#include "fsl_os_abstraction_bm.h"
#endif

#define Invalid()	output_string("\nInvalid Command\n")
#define Null_Ptr()	output_string("\nNull Pointer. Can't proceed. Abort.\n")

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;
typedef volatile uint8_t vuint8_t;
typedef volatile uint32_t	vuint32_t;

extern uint16_t *DMA_Buffer, *DMA_Buffer2;
extern uint16_t *var_ptr;
extern uint8_t ready, buff;

extern uint32_t volt;

#endif /* CUSTOM_MAIN_H_ */
