/*
 * custom_flash_program.c
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */
#ifdef	FRDM

#include "custom_flash_program.h"

//Functions for function pointer
//All are just printing things

//Access Error
void Access_Error_Print(void)
{
	PRINTF("%s", Access_Error_String);
}

//Read Collision Error
void Read_Collision_Error_Print(void)
{
	PRINTF("%s", Read_Collision_Error_String);
}

//Flash Protection Violation Error
void Flash_Protection_Violation_Error_Print(void)
{
	PRINTF("%s", Flash_Protection_Violation_String);
}

//Run Time Error
void Run_Time_Error_Print(void)
{
	PRINTF("%s", Run_Time_Error_String);
}

//Access Error & Read Collision Error
void Access_and_Collision_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Read_Collision_Error_Print();
}

//Access Error & Flash Protection Violation Error
void Access_and_Violation_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Flash_Protection_Violation_Error_Print();
}

//Access Error & Run Time Error
void Access_and_Run_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//Read Collision Error & Flash Protection Violation Error
void Collision_and_Violation_Error_Print(void)
{
	Read_Collision_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Flash_Protection_Violation_Error_Print();
}

//Read Collision Error & Run Time Error
void Collision_and_Run_Error_Print(void)
{
	Read_Collision_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//Flash Protection Violation Error & Run Time Error
void Violation_and_Run_Error_Print(void)
{
	Flash_Protection_Violation_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//Access Error & Read Collision Error & Flash Protection Violation Error
void Access_and_Collision_and_Violation_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Read_Collision_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Flash_Protection_Violation_Error_Print();
}

//Access Error & Read Collision Error & Run Time Error
void Access_and_Collision_and_Run_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Read_Collision_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//Access Error & Flash Protection Violation Error & Run Time Error
void Access_and_Violation_and_Run_Error_Print(void)
{
	Access_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Flash_Protection_Violation_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//Read Collision Error & Flash Protection Violation Error & Run Time Error
void Collision_and_Violation_and_Run_Error_Print(void)
{
	Read_Collision_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Flash_Protection_Violation_Error_Print();
	PRINTF("\n\r\tAND\t\n\r");
	Run_Time_Error_Print();
}

//All Errors
void All_Errors_Print(void)
{
	PRINTF("%s", All_Errors_String);
}

//Unknown Error
void Unknown_Error_Print(void)
{
	PRINTF("%s", Unknown_Error_String);
}

//Address out of Range Error
void Address_out_of_Range_Error_Print(void)
{
	PRINTF("%s", Address_out_of_Range_Error_String);
}

//Address out of Alignment Error
void Address_Alignment_Error_Print(void)
{
	PRINTF("%s", Address_Alignment_Error_String);
}

void Null_Pointer_Error_Print(void)
{
	PRINTF("%s", Null_Pointer_Error_String);
}

//Function pointer for error printing
void (*Error_Print_ptr[19]) (void) =
								{
									Access_Error_Print,
									Read_Collision_Error_Print,
									Flash_Protection_Violation_Error_Print,
									Run_Time_Error_Print,
									Access_and_Collision_Error_Print,
									Access_and_Violation_Error_Print,
									Access_and_Run_Error_Print,
									Collision_and_Violation_Error_Print,
									Collision_and_Run_Error_Print,
									Violation_and_Run_Error_Print,
									Access_and_Collision_and_Violation_Error_Print,
									Access_and_Collision_and_Run_Error_Print,
									Access_and_Violation_and_Run_Error_Print,
									Collision_and_Violation_and_Run_Error_Print,
									All_Errors_Print,
									Unknown_Error_Print,
									Address_out_of_Range_Error_Print,
									Address_Alignment_Error_Print,
									Null_Pointer_Error_Print
								};

//Global Variables
vuint32_t Flash_Data, Flash_Address, *Flash_Address_Pointer, *Flash_Buffer_Pointer;
vuint32_t Buffer[256];
volatile uint16_t flash_i;
vuint32_t sector_address = 0;
vuint32_t tdata;

void Flash_Sector_Read_Write_Sequence(vuint32_t *Address, vuint32_t Data)
{
	PRINTF("\n\rin seq\n\r");

	sector_address = ((uint8_t)((vuint32_t)Address / Sector_Size)) * Sector_Size;

	Flash_Buffer_Pointer = (vuint32_t*)sector_address;
	for(flash_i = 0; flash_i < 256; flash_i ++, Flash_Buffer_Pointer ++)
	{
//		PRINTF("\n\rin seq 2\n\r");
//		tdata = (vuint32_t)*Flash_Buffer_Pointer;
//		PRINTF("\n\rin seq 3\n\r");
		Buffer[flash_i] = 0xFFFFFFFF;
//		PRINTF("\n\ri: %d\n\r",flash_i);
	}
	flash_i = ((vuint32_t)Address - sector_address) / 4;
	PRINTF("\n\rout loop, flash i: %d\n\r",flash_i);
	Buffer[flash_i] = Data;
}

//Function to erase a sector in flash, based on the address that is to be written
int8_t Flash_Sector_Erase(vuint32_t *Address)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	sector_address = ((uint8_t)((vuint32_t)Address / Sector_Size)) * Sector_Size;

	//Checking whether the address is in limit
	if(((vuint32_t)Address < Flash_Memory_Lower_Limit) && ((vuint32_t)Address >= Flash_Memory_Upper_Limit))	\
			return (Address_Out_of_Range);

	//Checking whether the previous command (if any) has been completed or not
	Flash_Wait_for_CCIF();

	//Checking and clearing errors for previous command execution
	int8_t error;

	error = No_Error;
	error = Flash_Check_for_Error();
	if(error != No_Error)	Flash_Clear_all_Errors();

	//Writing parameters

	//First writing the command code to FCCOB0
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB0_Address), \
					(vuint8_t)FCMD_Erase_Sector);

	//Writing Address
	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB1
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB1_Address), \
					(vuint8_t)(GET_BIT_16_23(sector_address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15(sector_address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7(sector_address)));

	//Launching command and waiting for it to finish
	Flash_Execute_Command();
	Flash_Wait_for_CCIF();

	//Errors - if any - generated by this command
	error = No_Error;
	error = Flash_Check_for_Error();
	return (error);
}

//Function to verify whether the sector is erased or not
int8_t Flash_Sector_Verify(vuint32_t *Address)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	sector_address = ((uint8_t)((vuint32_t)Address / Sector_Size)) * Sector_Size;

	if(((vuint32_t)Address < Flash_Memory_Lower_Limit) && ((vuint32_t)Address >= Flash_Memory_Upper_Limit))	\
			return (Address_Out_of_Range);

	//Checking whether the previous command (if any) has been completed or not
	Flash_Wait_for_CCIF();

	//Checking and clearing errors for previous command execution
	int8_t error;

	error = No_Error;
	error = Flash_Check_for_Error();
	if(error != No_Error)	Flash_Clear_all_Errors();

	//Calculating number of longwords to verify, currently whole sector (256 longwords)
	uint16_t number_of_longwords = Sector_Size / Longword_Size;

	//Writing parameters

	//First writing the command code to FCCOB0
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB0_Address), \
					(vuint8_t)FCMD_Read_Ones_Section);

	//Writing Address
	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB1
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB1_Address), \
					(vuint8_t)(GET_BIT_16_23(sector_address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15(sector_address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7(sector_address)));

	//Writing Number of Longwords
	//Writing MSB Byte (0xFF00) to FCCOB4
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB4_Address), \
					(vuint8_t)(GET_BIT_8_15(number_of_longwords)));

	//Writing LSB Byte (0x00FF) to FCCOB5
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB5_Address), \
					(vuint8_t)(GET_BIT_0_7(number_of_longwords)));

	//Writing Margin Level
	//Using user margin to ensure that normal margin won't have any problems at all
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB6_Address), \
					(vuint8_t)User_Margin);

	//Launching command and waiting for it to finish
	Flash_Execute_Command();
	Flash_Wait_for_CCIF();

	//Errors - if any - generated by this command
	error = No_Error;
	error = Flash_Check_for_Error();
	return (error);
}

//Programming 32bit data in flash
int8_t Flash_Longword_Write(vuint32_t *Address, vuint32_t Data)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	//Checking for alignment
	if(Flash_Longword_Write_Address_Alignment((vuint32_t)Address))	\
			return (Flash_Program_Longword_Address_Alignment_Error);

	//Checking whether the address is in limit or not
	if(((vuint32_t)Address < Flash_Memory_Lower_Limit) || ((vuint32_t)Address >= Flash_Memory_Upper_Limit))		\
			return (Address_Out_of_Range);

	//Checking whether the previous command (if any) has been completed or not
	Flash_Wait_for_CCIF();

	//Checking and clearing errors for previous command execution
	int8_t error;

	error = No_Error;
	error = Flash_Check_for_Error();
	if(error != No_Error)	Flash_Clear_all_Errors();

	//Writing parameters

	//First writing the command code to FCCOB0
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB0_Address), \
					(vuint8_t)FCMD_Program_Longword);

	//Writing Address
	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB1
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB1_Address), \
					(vuint8_t)(GET_BIT_16_23((vuint32_t)Address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15((vuint32_t)Address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7((vuint32_t)Address)));

	//Writing Data
	//Writing MSB Byte (0xFF00_0000) to FCCOB4
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB4_Address), \
					(vuint8_t)(GET_BIT_24_31(Data)));

	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB5
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB5_Address), \
					(vuint8_t)(GET_BIT_16_23(Data)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB6
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB6_Address), \
					(vuint8_t)(GET_BIT_8_15(Data)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB7
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB7_Address), \
					(vuint8_t)(GET_BIT_0_7(Data)));

	//Launching command and waiting for it to finish
	Flash_Execute_Command();
	Flash_Wait_for_CCIF();

	//Errors - if any - generated by this command
	error = No_Error;
	error = Flash_Check_for_Error();
	return (error);
}

int8_t Flash_Longword_Verify(vuint32_t *Address, vuint32_t Data)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	//Checking for alignment
	if(Flash_Longword_Write_Address_Alignment((vuint32_t)Address))	\
			return (Flash_Program_Longword_Address_Alignment_Error);

	//Checking whether the address is in limit or not
	if(((vuint32_t)Address < Flash_Memory_Lower_Limit) || ((vuint32_t)Address >= Flash_Memory_Upper_Limit))	\
			return (Address_Out_of_Range);

	//Checking whether the previous command (if any) has been completed or not
	Flash_Wait_for_CCIF();

	//Checking and clearing errors for previous command execution
	int8_t error;

	error = No_Error;
	error = Flash_Check_for_Error();
	if(error != No_Error)	Flash_Clear_all_Errors();

	//Writing parameters

	//First writing the command code to FCCOB0
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB0_Address), \
					(vuint8_t)FCMD_Program_Check);

	//Writing Address
	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB1
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB1_Address), \
					(vuint8_t)(GET_BIT_16_23((vuint32_t)Address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15((vuint32_t)Address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7((vuint32_t)Address)));

	//Writing Margin Level
	//Using user margin to ensure that normal margin won't have any problems at all
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB4_Address), \
					(vuint8_t)(vuint8_t)User_Margin);

	//Writing Data
	//Writing MSB Byte (0xFF00_0000) to FCCOB8
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB8_Address), \
					(vuint8_t)(GET_BIT_24_31(Data)));

	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB9
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB9_Address), \
					(vuint8_t)(GET_BIT_16_23(Data)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOBA
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOBA_Address), \
					(vuint8_t)(GET_BIT_8_15(Data)));

	//Writing LSB Byte (0x0000_00FF) to FCCOBB
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOBB_Address), \
					(vuint8_t)(GET_BIT_0_7(Data)));

	//Launching command and waiting for it to finish
	Flash_Execute_Command();
	Flash_Wait_for_CCIF();

	//Errors - if any - generated by this command
	error = No_Error;
	error = Flash_Check_for_Error();
	return (error);
}


//Flash Error Handler
void Flash_Error_Handler(int8_t Error_Code)
{
	//Basic Switch Case to use function pointer correctly
	uint8_t lookup;
	switch(Error_Code)
	{
		case Null_Pointer:
		{
			lookup = Null_Pointer_Error_Code;
			break;
		}
		case Address_Out_of_Range:
		{
			lookup = Address_out_of_Range_Code;
			break;
		}
		case Flash_Program_Longword_Address_Alignment_Error:
		{
			lookup = Flash_Program_Longword_Address_Alignment_Error_Code;
			break;
		}
		case (1 << FSTAT_ACCERR_Position):
		{
			lookup = Access_Error;
			break;
		}
		case (1 << FSTAT_RDCOLERR_Position):
		{
			lookup = Read_Collision_Error;
			break;
		}
		case (1 << FSTAT_FPVIOL_Position):
		{
			lookup = Flash_Protection_Violation;
			break;
		}
		case (1 << FSTAT_MGSTAT0_Position):
		{
			lookup = Run_Time_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_RDCOLERR_Position)):
		{
			lookup = Access_and_Read_Collision_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_FPVIOL_Position)):
		{
			lookup = Access_and_Flash_Violation_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Access_and_Run_Time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_RDCOLERR_Position) | (1 << FSTAT_FPVIOL_Position)):
		{
			lookup = Read_Collision_and_Flash_Violation_Combined_Error;
			break;
		}
		case ((1 << FSTAT_RDCOLERR_Position) | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Read_Collision_and_Run_Time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_FPVIOL_Position) | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Flash_Violation_and_Run_Time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_RDCOLERR_Position) \
				 | (1 << FSTAT_FPVIOL_Position)):
		{
			lookup = Access_and_Read_Collision_and_Flash_Violation_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_RDCOLERR_Position) \
				 | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Access_and_Read_Collision_and_Run_time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_FPVIOL_Position) \
				 | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Access_and_Flash_Violation_and_Run_time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_RDCOLERR_Position) | (1 << FSTAT_FPVIOL_Position) \
				 | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = Read_Collision_and_Flash_Violation_and_Run_time_Combined_Error;
			break;
		}
		case ((1 << FSTAT_ACCERR_Position) | (1 << FSTAT_RDCOLERR_Position) \
				 | (1 << FSTAT_FPVIOL_Position) | (1 << FSTAT_MGSTAT0_Position)):
		{
			lookup = All_Combined_Error;
			break;
		}
		default:
		{
			lookup = Unknown_Error;
		}
	}

	//Subtracting 1 to correct the indexing
	lookup -= 1;

	//Function Pointer
	(*Error_Print_ptr[lookup])();
}

int8_t test(vuint32_t *Address)
{

		sector_address = (vuint32_t)Address;
		sector_address /= Sector_Size;
		sector_address *= Sector_Size;
		vuint8_t tmp;
//		sector_address = ((uint8_t)((vuint32_t)Address / Sector_Size)) * Sector_Size;

		PRINTF("\n\rsect: %x\n\r", sector_address);

		//Checking whether the previous command (if any) has been completed or not
		Flash_Wait_for_CCIF();

		//Checking and clearing errors for previous command execution
		int8_t error;

		error = No_Error;
		error = Flash_Check_for_Error();
		if(error != No_Error)	Flash_Clear_all_Errors();

		//Writing parameters

		tmp = (vuint8_t)FCMD_Erase_Sector;
		//First writing the command code to FCCOB0
		REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB0_Address), \
				tmp);

		//Writing Address
		//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB1
		tmp = (vuint8_t)(GET_BIT_16_23(sector_address));
		REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB1_Address), \
				tmp);


		//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
		tmp = (vuint8_t)(GET_BIT_8_15(sector_address));
		REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
				tmp);

		//Writing LSB Byte (0x0000_00FF) to FCCOB3
		tmp = (vuint8_t)(GET_BIT_0_7(sector_address));
		REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
				tmp);

		//Launching command and waiting for it to finish
		Flash_Execute_Command();
		Flash_Wait_for_CCIF();

		//Errors - if any - generated by this command
		error = No_Error;
		error = Flash_Check_for_Error();
		if(error)		return(error);
		else	PRINTF("\n\rErase Success\n\r");
		return 0;
}

//Main Function which uses all 4 - Erase, Read 1s, Write, Check
int8_t Flash_Program(vuint32_t *Address, vuint32_t Data)
{
	//Clearing all errors first
	Flash_Clear_all_Errors();

	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	sector_address = ((uint8_t)((vuint32_t)Address / Sector_Size)) * Sector_Size;

	//Useful printing
	PRINTF("The data to be written at address %x is %x\n\r", (vuint32_t)Address, Data);
	PRINTF("\n\rStarting Operation\n\r");

	Flash_Sector_Read_Write_Sequence(Address, Data);

	//Variable to relay the returns
	int8_t return_value;

	return_value = Flash_Sector_Erase(Address);
	if(return_value != No_Error)
	{
		PRINTF("Erase Returned with the following error:\n\r");
		return (return_value);
	}
	PRINTF("\n\rSector Erased Successfully\n\r");

	return_value = Flash_Sector_Verify(Address);
	if(return_value != No_Error)
	{
		PRINTF("Erase Verification Returned with the following error:\n\r");
		return (return_value);
	}
	PRINTF("\n\rSector Erase Verified Successfully\n\r");

	Flash_Buffer_Pointer = (vuint32_t*)sector_address;
	for(flash_i = 0; flash_i < 256; flash_i ++, Flash_Buffer_Pointer ++)
	{
		return_value = Flash_Longword_Write(Flash_Buffer_Pointer, Buffer[flash_i]);
		if(return_value != No_Error)
		{
			PRINTF("Flash Longword Write Returned with the following error:\n\r");
			return (return_value);
		}
	}
	PRINTF("\n\rLongword written Successfully\n\r");

	Flash_Buffer_Pointer = (vuint32_t*)sector_address;
	for(flash_i = 0; flash_i < 256; flash_i ++, Flash_Buffer_Pointer ++)
	{
		return_value = Flash_Longword_Verify(Flash_Buffer_Pointer, Buffer[flash_i]);
		if(return_value != No_Error)
		{
			PRINTF("\n\rFlash Longword Verified Returned with the following error:\n\r");
			return (return_value);
		}
	}
	PRINTF("\n\rLongword verified Successfully\n\r");

	return (No_Error);
}

#endif
