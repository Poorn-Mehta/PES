#ifndef __Input_h__
#define __Input_h__

#include "Main.h"
#include "Help.h"
#include "Memalloc.h"
#include "Memfree.h"
#include "Memwrite.h"
#include "Memread.h"
#include "Meminv.h"
#include "Patterngen.h"
#include "Patternverify.h"

#define Number_of_Input_Functions	9

extern const char ire[], i1[], i2[], i3[], i4[], i5[], i6[], i7[], i8[], i9[];
extern void (*Input_Func_Pointer[9]) (void);
extern void (*Input_Space_Func_Pointer[9]) (void);

extern char input_array[500], error_flag, hex_flag;
extern uint8_t input_i, input_j, input_k;

void Command_Error(void);
void Exit_Func(void);
void Memalloc_Func(void);
void Space_Memalloc_Func(void);
void Memfree_Func(void);
void Memwrite_Func(void);
void Space_Memwrite_Func(void);
void Memread_Func(void);
void Space_Memread_Func(void);
void Meminv_Func(void);
void Space_Meminv_Func(void);
void Patterngen_Func(void);
void Space_Patterngen_Func(void);
void Patternverify_Func(void);
void Space_Patternverify_Func(void);


void Input_Init(void);
void Input_Cleanup(void);
void Valid_Integer_Input(void);
void String_to_Decimal(char *stod_ptr);
void String_to_Hex(char *stox_ptr);
void Input_Lookup(void);

#endif
