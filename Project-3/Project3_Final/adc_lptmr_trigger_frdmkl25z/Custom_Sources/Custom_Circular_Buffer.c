/*
 * Custom_Circular_Buffer.c
 *
 *  Created on: Nov 14, 2018
 *      Author: poorn
 */

#include "Custom_Circular_Buffer.h"

//Variables

CBuffer CBuffer_Instance[Maximum_Buffers];
ptr_type Location, Continuous_Read;
Byte CBuffer_Data, Error, No_of_CBuffers, cbuffer_i, cbuffer_j;
char CBuffer_Input[10];
DWord CBuffer_Instance_Length[Maximum_Buffers], value;
Byte return_value;
Byte resize = 0;


//Function to get values from string - SCANF can be used instead of FGETS

void String_to_Decimal(char *stod_ptr)
{
	if(stod_ptr)
	{
		char *stod_i;
		stod_i = stod_ptr;
		for(; *stod_ptr != 0; stod_ptr ++)
		{
			if(isdigit(*stod_ptr) == 0)
			{
				Output_String("\n\r\rNon Integer Value Entered\n\r\r");
				Error = 1;
				value = 0;
				break;
			}
		}
		if(*stod_ptr == 0)
		{
			Error = 0;
			value = atoi(stod_i);
		}
	}
	else
	{
		Output_String("\n\rNull Pointer\n\r");
		Error = 1;
		value = 0;
	}
}

// Initializing each of the buffers

Byte CBuffer_Assign(Byte CBuffer_ID)
{
	CBuffer_Instance[CBuffer_ID].Length = CBuffer_Instance_Length[CBuffer_ID];
	CBuffer_Instance[CBuffer_ID].Elements_count = 0;
	CBuffer_Instance[CBuffer_ID].Start_ptr = (Byte *)malloc(CBuffer_Instance_Length[CBuffer_ID]);
	if(CBuffer_Instance[CBuffer_ID].Start_ptr == 0)		return 1;
	CBuffer_Instance[CBuffer_ID].Head = 0;
	CBuffer_Instance[CBuffer_ID].Tail = 0;
	CBuffer_Instance[CBuffer_ID].Index = 0;
	CBuffer_Instance[CBuffer_ID].Status = Empty;
	return 0;
}

//Input about buffers from user

Byte CBuffer_Init(void)
{
	No_of_CBuffers = 2;
	CBuffer_Instance_Length[FGETS_Buffer_ID] = FGETS_Buffer_Length;
//	if(CBuffer_Assign(FGETS_Buffer_ID))		return 1;
	//Get length of each, store it in array called CBuffer_Instance_Length
	for(cbuffer_i = 1; cbuffer_i < No_of_CBuffers; cbuffer_i ++)
	{
		Output_String("\n\rEnter the length of ");
		Output_String("Rx Buffer: ");
		Input_String(CBuffer_Input, FGETS_Buffer_Length, stdin);
		cbuffer_j = 0;
		while(CBuffer_Input[cbuffer_j] != Enter_Detected)		cbuffer_j ++;
		CBuffer_Input[cbuffer_j] = 0;
		Output_String("\n\rLength set: ");
		String_to_Decimal(CBuffer_Input);
		if(Error)		return 1;
		CBuffer_Instance_Length[cbuffer_i] = value;
		sprintf(CBuffer_Input, "%ld", value);
		Output_String(CBuffer_Input);
	}

	//Initialize each buffer
	for(cbuffer_i = 1; cbuffer_i < No_of_CBuffers; cbuffer_i ++)
	{
		if(CBuffer_Assign(cbuffer_i))	return 1;
	}
	return 0;
}

//Function to write 1 byte in given buffer

Byte CBuffer_Byte_Write(Byte CBuffer_ID, Byte data)
{
	//If buffer is non empty and head meets the tail then buffer is full and overwriting
//	if((CBuffer_Instance[CBuffer_ID].Status != Empty) && (CBuffer_Instance[CBuffer_ID].Head == CBuffer_Instance[CBuffer_ID].Tail))
//	{
//		CBuffer_Instance[CBuffer_ID].Status = Full;
//		return_value = Overwriting;
//	}
	if(CBuffer_Instance[CBuffer_ID].Elements_count == CBuffer_Instance[CBuffer_ID].Length)
	{
		CBuffer_Instance[CBuffer_ID].Status = Full;
		return_value = Overwriting;
	}
	else
	{
		if(return_value != Overwriting)		return_value = Success;
	}

	//Attempt to not lose data even when buffer is full
//	if(return_value == Overwriting)
//	{
//		CBuffer_Instance[CBuffer_ID].Start_ptr = (Byte *)realloc(CBuffer_Instance[CBuffer_ID].Start_ptr, CBuffer_Instance_Length[CBuffer_ID]);
//		CBuffer_Instance[CBuffer_ID].Head = CBuffer_Instance[CBuffer_ID].Length;
//		CBuffer_Instance[CBuffer_ID].Length += CBuffer_Instance_Length[CBuffer_ID];
//		CBuffer_Instance[CBuffer_ID].Status = Success;
//		return_value = Success;
//	}

	//Write data using start pointer + relative address from head
	*(CBuffer_Instance[CBuffer_ID].Start_ptr + CBuffer_Instance[CBuffer_ID].Head) = data;


	//Joining end to start - that is if head is at the end, instead of incrementing, wrap it back to the start (0)
	if(CBuffer_Instance[CBuffer_ID].Head == (CBuffer_Instance[CBuffer_ID].Length - 1))	CBuffer_Instance[CBuffer_ID].Head = 0;
	else	CBuffer_Instance[CBuffer_ID].Head += 1;

	//Raising this flag after actual write is necessary for other functions
	if(CBuffer_Instance[CBuffer_ID].Head == CBuffer_Instance[CBuffer_ID].Tail)	CBuffer_Instance[CBuffer_ID].Status = Full;

	//Change status flag if wrote to empty buffer
	if(CBuffer_Instance[CBuffer_ID].Status == Empty)	CBuffer_Instance[CBuffer_ID].Status = Success;

	//Read chain broke down by writing
	Continuous_Read = 0;

	//Added element, increment count
	if(CBuffer_Instance[CBuffer_ID].Status != Full)	CBuffer_Instance[CBuffer_ID].Elements_count += 1;
	else	CBuffer_Instance[CBuffer_ID].Elements_count = CBuffer_Instance[CBuffer_ID].Length;
	return (return_value);
}

Byte CBuffer_Byte_Read(Byte CBuffer_ID, Byte *address)
{
	if(return_value == Overwriting)		return_value = Success;

	//If read the whole buffer then mark it as empty
	if(Continuous_Read == CBuffer_Instance[CBuffer_ID].Length)
	{
		CBuffer_Instance[CBuffer_ID].Tail = CBuffer_Instance[CBuffer_ID].Head;
		CBuffer_Instance[CBuffer_ID].Status = Empty;
		Output_String("e1");
		return (Empty);
	}
	else
	{
		//Hasn't performed maximum number of reads but, tail and head meet
		if(CBuffer_Instance[CBuffer_ID].Tail == CBuffer_Instance[CBuffer_ID].Head)
		{
			//If buffer wasn't full then it is empty now
			if(CBuffer_Instance[CBuffer_ID].Status != Full)
			{
				CBuffer_Instance[CBuffer_ID].Status = Empty;
				Output_String("e2");
				return (Empty);
			}

			//If the buffer was full then update the index to mark that this will be the new tail starting location after reading everything
			else
			{
				CBuffer_Instance[CBuffer_ID].Index = CBuffer_Instance[CBuffer_ID].Tail;
				CBuffer_Instance[CBuffer_ID].Status = Success;
			}
		}
	}

	//read using pointer
	*address = *(CBuffer_Instance[CBuffer_ID].Start_ptr + CBuffer_Instance[CBuffer_ID].Tail);

	//joining end to start to make a circular path
		if(CBuffer_Instance[CBuffer_ID].Tail == (CBuffer_Instance[CBuffer_ID].Length - 1))	CBuffer_Instance[CBuffer_ID].Tail = 0;
		else	CBuffer_Instance[CBuffer_ID].Tail += 1;

	//increases continuous read variable
	Continuous_Read += 1;

	if(CBuffer_Instance[CBuffer_ID].Tail == CBuffer_Instance[CBuffer_ID].Head)
	{
		if(CBuffer_Instance[CBuffer_ID].Status != Full)
		{
			Output_String("e3");
			CBuffer_Instance[CBuffer_ID].Status = Empty;
		}
	}

	//element removed
	if(CBuffer_Instance[CBuffer_ID].Elements_count > 0)		CBuffer_Instance[CBuffer_ID].Elements_count -= 1;
	return (Success);
}

//Function to handle both read and write
void CBuffer_Operation(Byte CBuffer_ID, Byte type, Byte data, Byte *address)
{
	if(type == Write)
	{
		//the only error is overwriting warning
		if(CBuffer_Byte_Write(CBuffer_ID, data))	Output_String("Buffer%d Full, Overwriting\n\r", CBuffer_ID);

		//printing useful information
		Location = CBuffer_Instance[CBuffer_ID].Head;
		if(Location)		Location -= 1;
		else	Location = CBuffer_Instance[CBuffer_ID].Length - 1;
		Output_String("Wrote %c at %d in buffer%d", data, Location, CBuffer_ID);
	}
	else if(type == Read)
	{
		//only error is buffer empty
		if(CBuffer_Byte_Read(CBuffer_ID, address))
		{
			Output_String("Buffer%d Empty\n\r", CBuffer_ID);
		}
		else
		{
			Location = CBuffer_Instance[CBuffer_ID].Tail;
			if(Location)		Location -= 1;
			else	Location = CBuffer_Instance[CBuffer_ID].Length - 1;
			Output_String("Read return is %c from %d in buffer%d", CBuffer_Data, Location, CBuffer_ID);
		}
	}
}

DWord CBuffer_Elements(Byte CBuffer_ID)
{
	return (CBuffer_Instance[CBuffer_ID].Elements_count);
}

//resizing existing buffer
Byte CBuffer_Resize(Byte CBuffer_ID)
{
	Output_String("\n\rEnter new length of buffer%d: ", CBuffer_ID);
	Input_String(CBuffer_Input, 10, stdin);
	cbuffer_j = 0;
	while(CBuffer_Input[cbuffer_j] != Enter_Detected)		cbuffer_j ++;
	CBuffer_Input[cbuffer_j] = 0;
	String_to_Decimal(CBuffer_Input);
	if(Error)		return 1;
	free(CBuffer_Instance[CBuffer_ID].Start_ptr);
	CBuffer_Instance_Length[CBuffer_ID] = value;
	CBuffer_Assign(CBuffer_ID);
	return 0;
}
