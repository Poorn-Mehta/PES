/*
 * Custom_Circular_Buffer.h
 *
 *  Created on: Nov 14, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_CIRCULAR_BUFFER_H_
#define CUSTOM_CIRCULAR_BUFFER_H_

#include "Custom_Main.h"

#define TEST	1


#define Success			0
#define Overwriting		1
#define Empty			2
#define Full			3
#define Write			0
#define Read			1


typedef struct
{
	Byte *Start_ptr;
	Byte Status;
	DWord Length;
	DWord Elements_count;
	ptr_type Head;
	ptr_type Tail;
	ptr_type Index;
}CBuffer;

#define Maximum_Buffers		10

extern CBuffer CBuffer_Instance[Maximum_Buffers];
extern Byte CBuffer_Data, Error, No_of_CBuffers;
extern ptr_type Location, Continuous_Read;
extern char CBuffer_Input[10];
extern DWord CBuffer_Instance_Length[Maximum_Buffers], value;


void String_to_Decimal(char *stod_ptr);
Byte CBuffer_Assign(Byte CBuffer_ID);
#if TEST
Byte CBuffer_Init(DWord len1, DWord len2);
Byte CBuffer_Resize(Byte CBuffer_ID, DWord nlen);
#else
Byte CBuffer_Init(void);
Byte CBuffer_Resize(Byte CBuffer_ID);
#endif
Byte CBuffer_Byte_Write(Byte CBuffer_ID, Byte data);
Byte CBuffer_Byte_Read(Byte CBuffer_ID, Byte *address);
void CBuffer_Operation(Byte CBuffer_ID, Byte type, Byte data, Byte *address);
DWord CBuffer_Elements(Byte CBuffer_ID);



#endif /* CUSTOM_CIRCULAR_BUFFER_H_ */

