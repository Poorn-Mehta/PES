#ifndef __Help_h__
#define __Help_h__

#include "Main.h"

#define Number_of_Help_Functions		8

extern const char h[], hd[], h1[], h2[], h3[], h4[], h5[], h6[], h7[], h8[], hre[], hr1[], hr2[], hr3[], hr4[], hr5[], hr6[], hr7[], hr8[];
extern char help_array[];

extern char help_print[500];
extern uint8_t help_i, help_j, help_k;
extern void (*Help_Func_Ptr[8]) (void);

void Help_Init(void);
void Help_Display(void);
void Help_Lookup(void);

void Help_Response1(void);
void Help_Response2(void);
void Help_Response3(void);
void Help_Response4(void);
void Help_Response5(void);
void Help_Response6(void);
void Help_Response7(void);
void Help_Response8(void);

#endif
