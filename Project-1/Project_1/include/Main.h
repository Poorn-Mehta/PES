#ifndef __Main_h__
#define __Main_h__

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define Invalid()	printf("\nInvalid Command\n")
#define Null_Ptr()	printf("\nNull Pointer. Can't proceed. Abort.\n")

extern char input[250], input1[50], input2[50], input3[50], input4[50], input5[50];
extern uint8_t main_i, main_j, exit_flag, space_flag, relative_address;
extern uint64_t value, value1, value2, value3, value4;

extern char m_print[50];
extern uint8_t print;

extern uint8_t boundary_error;
extern char b_input[50];
extern uint8_t b_proceed;

extern clock_t t;

extern uint32_t *mem_ptr, *mem_ptr2, mem_max, *mem_original;

void Array_Cleanup(char *clean_ptr);
void Detailed_Output(void);
void clkbegin(void);
void clkend(void);
void Boundary_Check(void);





#endif
