/****************************************************************************
 (c) Copyright 2010-2015 Freescale Semiconductor, Inc.
 ALL RIGHTS RESERVED.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************

*****************************************************************************
*                                                                           *
*        Standard Software Flash Driver For FTFx                            *
*                                                                           *
* FILE NAME     :  SSD_FTFx.h                                               *
* DATE          :  Sep 25, 2014                                           *
*                                                                           *
* AUTHOR        :  FPT Team                                                 *
* E-mail        :  r56611@freescale.com                                     *
*                                                                           *
*****************************************************************************/

/************************** CHANGES *************************************
1.1.GA      09.25.2014      FPT Team      First version of SDK C90TFS flash driver
                                          inherited from BM C90TFS flash driver v1.02
                                          (08.04.2014, FPT Team)
1.3.GA      06.23.2015      ROM Team      Added FAC Error Status
*************************************************************************/

//#include "MKL25Z4.h"

#include<stdio.h>
#include<stdint.h>

//Flash register addresses
#define FTFA_Address_Offset		(0x4002 << 16)
#define FTFA_FSTAT_Address		0x0000
#define FTFA_FCNFG_Address		0x0001
#define FTFA_FSEC_Address		0x0002
#define FTFA_FOPT_Address		0x0003
#define FTFA_FCCOB0_Address		0x0007
#define FTFA_FCCOB1_Address		0x0006
#define FTFA_FCCOB2_Address		0x0005
#define FTFA_FCCOB3_Address		0x0004
#define FTFA_FCCOB4_Address		0x000B
#define FTFA_FCCOB5_Address		0x000A
#define FTFA_FCCOB6_Address		0x0009
#define FTFA_FCCOB7_Address		0x0008
#define FTFA_FCCOB8_Address		0x000F
#define FTFA_FCCOB9_Address		0x000E
#define FTFA_FCCOBA_Address		0x000D
#define FTFA_FCCOBB_Address		0x000C
#define FTFA_FPROT3_Address		0x0010
#define FTFA_FPROT2_Address		0x0011
#define FTFA_FPROT1_Address		0x0012
#define FTFA_FPROT0_Address		0x0013

//Flash status register bit positions
#define FSTAT_CCIF_Position			7
#define FSTAT_RDCOLERR_Position		6
#define FSTAT_ACCERR_Position		5
#define FSTAT_FPVIOL_Position		4
#define FSTAT_MGSTAT0_Position		0

//Flash configuration register bit positions
#define FCNFG_CCIE_Position			7
#define FCNFG_RDCOLLIE_Position		6
#define FCNFG_ERSAREQ_Position		5
#define FCNFG_ERSSUSP_Position		4

//Flash security register bit positions
#define FSEC_KEYEN_H_Position		7
#define FSEC_KEYEN_L_Position		6
#define FSEC_MEEN_H_Position		5
#define FSEC_MEEN_L_Position		4
#define FSEC_FSLACC_H_Position		3
#define FSEC_FSLACC_L_Position		2
#define FSEC_SEC_H_Position			1
#define FSEC_SEC_L_Position			0

//Flash Command codes
#define FCMD_Read_Ones_Section		0x01
#define FCMD_Program_Check			0x02
#define FCMD_Read_Resource			0x03
#define FCMD_Program_Longword		0x06
#define FCMD_Erase_Sector			0x09
#define FCMD_Read_Ones_Block		0x40
#define FCMD_Read_Once				0x41
#define FCMD_Program_Once			0x43
#define FCMD_Erase_All_Blocks		0x44
#define FCMD_Verify_Backdoor_Access_Key		0x45

//Generic names
#define Flash_Command_Register					FTFA_FCCOB0_Address
#define Flash_Address_Most_Significant_Byte		FTFA_FCCOB1_Address
#define Flash_Address_Middle_Byte				FTFA_FCCOB2_Address
#define Flash_Address_Least_Significant_Byte	FTFA_FCCOB3_Address
#define Flash_Data_Most_Significant_Byte		FTFA_FCCOB4_Address
#define Flash_Data_Seventh_Byte					FTFA_FCCOB5_Address
#define Flash_Data_Sixth_Byte					FTFA_FCCOB6_Address
#define Flash_Data_Fifth_Byte					FTFA_FCCOB7_Address
#define Flash_Data_Fourth_Byte					FTFA_FCCOB8_Address
#define Flash_Data_Third_Byte					FTFA_FCCOB9_Address
#define Flash_Data_Second_Byte					FTFA_FCCOBA_Address
#define Flash_Data_Least_Significant_Byte		FTFA_FCCOBB_Address

//Flash Defines
#define User_Margin					0x01
#define Sector_Size					1024 //bytes
#define Longword_Size				4	//bytes
#define Flash_Memory_Lower_Limit	0x400	//skipping first 1kB as various data is in there
#define Flash_Memory_Upper_Limit	0x20000

//Change this values to check different things
#define Flash_Address_to_Write		0x1FF00
#define Flash_Data_to_Write			0xAA55FF00

//For error function pointer lookup value
#define Address_out_of_Range_Code	17
#define Flash_Program_Longword_Address_Alignment_Error_Code		18
#define Null_Pointer_Error_Code		19

typedef volatile uint8_t vuint8_t;
typedef volatile uint32_t	vuint32_t;

//check the alignment for longword program operation
#define Flash_Longword_Write_Address_Alignment(addr)		(addr & (0x03))

//macros useful for register read and write
//these macros are taken from file written by NXP engineers
#define REG_BIT_SET(address, mask)      (*(vuint8_t*)(address) |= (mask))
#define REG_BIT_CLEAR(address, mask)    (*(vuint8_t*)(address) &= ~(mask))
#define REG_BIT_GET(address, mask)      (*(vuint8_t*)(address) & (uint8_t)(mask))
#define REG_WRITE(address, value)       (*(vuint8_t*)(address) = (value))
#define REG_READ(address)               ((uint8_t)(*(vuint8_t*)(address)))
#define GET_BIT_0_7(value)              ((uint8_t)((value) & 0xFFU))
#define GET_BIT_8_15(value)             ((uint8_t)(((value)>>8) & 0xFFU))
#define GET_BIT_16_23(value)            ((uint8_t)(((value)>>16) & 0xFFU))
#define GET_BIT_24_31(value)            ((uint8_t)((value)>>24))

//My own macros

//Waiting for CCIF to become 1
#define Flash_Wait_for_CCIF(void)		while(!(REG_BIT_GET((FTFA_Address_Offset + FTFA_FSTAT_Address), \
										(1 << FSTAT_CCIF_Position))))

//Writing 1 to CCIF and effectively clearing it (to state 0) to launch the command
#define Flash_Execute_Command(void)		REG_BIT_SET((FTFA_Address_Offset + FTFA_FSTAT_Address), \
										(1 << FSTAT_CCIF_Position))

//Returning all possible error bits' status
#define Flash_Check_for_Error(void)		(REG_READ(FTFA_Address_Offset + FTFA_FSTAT_Address) & \
										((1 << FSTAT_RDCOLERR_Position) | \
										(1 << FSTAT_ACCERR_Position) | \
										(1 << FSTAT_FPVIOL_Position) | \
										(1 << FSTAT_MGSTAT0_Position)))

//Clearing all errors
#define Flash_Clear_all_Errors(void)	(REG_WRITE((FTFA_Address_Offset + FTFA_FSTAT_Address), \
										((1 << FSTAT_RDCOLERR_Position) | \
										(1 << FSTAT_ACCERR_Position) | \
										(1 << FSTAT_FPVIOL_Position))))

//Error print messages - currently not useful because debugging is not included
//However could come in handy
//Combinations of these messages are used for combined error printing
const char Access_Error_String[] = "\nExecuted Command was unable to Access Flash\n";
const char Read_Collision_Error_String[] = "\nMCU Attempted Read while Flash Command was Running\n";
const char Flash_Protection_Violation_String[] = "\nExecuted Command at provided Flash Address\ndetected flash protection violation\n";
const char Run_Time_Error_String[] = "\nExecuted Command ran into Run Time Error\n";
const char All_Errors_String[] = "\nCongratulations :D You ran into ALL of the ERRORS\n";
const char Unknown_Error_String[] = "\nWho knows what happened :/\n\nBetter luck next time :P\n";
const char Address_out_of_Range_Error_String[] = "\nProvided Flash Address is Out of Range\n";
const char Address_Alignment_Error_String[] = "\nProvided Flash Address is not aligning with Longword Access\n";
const char Null_Pointer_Error_String[] = "\nNull Pointer Passed\n";

//Functions for function pointer
//All are just printing things

//Access Error
void Access_Error_Print(void)
{
	printf("%s", Access_Error_String);
}

//Read Collision Error
void Read_Collision_Error_Print(void)
{
	printf("%s", Read_Collision_Error_String);
}

//Flash Protection Violation Error
void Flash_Protection_Violation_Error_Print(void)
{
	printf("%s", Flash_Protection_Violation_String);
}

//Run Time Error
void Run_Time_Error_Print(void)
{
	printf("%s", Run_Time_Error_String);
}

//Access Error & Read Collision Error
void Access_and_Collision_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Read_Collision_Error_Print();
}

//Access Error & Flash Protection Violation Error
void Access_and_Violation_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Flash_Protection_Violation_Error_Print();
}

//Access Error & Run Time Error
void Access_and_Run_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//Read Collision Error & Flash Protection Violation Error
void Collision_and_Violation_Error_Print(void)
{
	Read_Collision_Error_Print();
	printf("\n\tAND\t\n");
	Flash_Protection_Violation_Error_Print();
}

//Read Collision Error & Run Time Error
void Collision_and_Run_Error_Print(void)
{
	Read_Collision_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//Flash Protection Violation Error & Run Time Error
void Violation_and_Run_Error_Print(void)
{
	Flash_Protection_Violation_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//Access Error & Read Collision Error & Flash Protection Violation Error
void Access_and_Collision_and_Violation_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Read_Collision_Error_Print();
	printf("\n\tAND\t\n");
	Flash_Protection_Violation_Error_Print();
}

//Access Error & Read Collision Error & Run Time Error
void Access_and_Collision_and_Run_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Read_Collision_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//Access Error & Flash Protection Violation Error & Run Time Error
void Access_and_Violation_and_Run_Error_Print(void)
{
	Access_Error_Print();
	printf("\n\tAND\t\n");
	Flash_Protection_Violation_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//Read Collision Error & Flash Protection Violation Error & Run Time Error
void Collision_and_Violation_and_Run_Error_Print(void)
{
	Read_Collision_Error_Print();
	printf("\n\tAND\t\n");
	Flash_Protection_Violation_Error_Print();
	printf("\n\tAND\t\n");
	Run_Time_Error_Print();
}

//All Errors
void All_Errors_Print(void)
{
	printf("%s", All_Errors_String);
}

//Unknown Error
void Unknown_Error_Print(void)
{
	printf("%s", Unknown_Error_String);
}

//Address out of Range Error
void Address_out_of_Range_Error_Print(void)
{
	printf("%s", Address_out_of_Range_Error_String);
}

//Address out of Alignment Error
void Address_Alignment_Error_Print(void)
{
	printf("%s", Address_Alignment_Error_String);
}

void Null_Pointer_Error_Print(void)
{
	printf("%s", Null_Pointer_Error_String);
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

//All possible errors are defined here
typedef enum {
	Null_Pointer = -3,
	Address_Out_of_Range = -2,
	Flash_Program_Longword_Address_Alignment_Error = -1,
	No_Error,
	Access_Error,
	Read_Collision_Error,
	Flash_Protection_Violation,
	Run_Time_Error,
	Access_and_Read_Collision_Combined_Error,
	Access_and_Flash_Violation_Combined_Error,
	Access_and_Run_Time_Combined_Error,
	Read_Collision_and_Flash_Violation_Combined_Error,
	Read_Collision_and_Run_Time_Combined_Error,
	Flash_Violation_and_Run_Time_Combined_Error,
	Access_and_Read_Collision_and_Flash_Violation_Combined_Error,
	Access_and_Read_Collision_and_Run_time_Combined_Error,
	Access_and_Flash_Violation_and_Run_time_Combined_Error,
	Read_Collision_and_Flash_Violation_and_Run_time_Combined_Error,
	All_Combined_Error,
	Unknown_Error
}Flash_Errors;

//Global Variables
vuint32_t Flash_Data, Flash_Address, *Flash_Address_Pointer;

//Function to erase a sector in flash, based on the address that is to be written
int8_t Flash_Sector_Erase(vuint32_t *Address)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	vuint32_t sector_address = 0;

	//Checking whether the address is in limit
	if((*Address >= Flash_Memory_Lower_Limit) && (*Address < Flash_Memory_Upper_Limit))
	{
		//Calculating sector starting address from provided longword address
		//It is done by converting float to integer and getting rid of
		//numbers after decimal point. For example, for the address of 2100
		//it will first do the 2100/1024, which will return 2.<some_numbers>
		//but since the result is cast as unsigned char, it will only store 2
		//Then 2 is multiplied by 1024, which is the starting address of
		//the sector in which 2100 lies
		sector_address = ((uint8_t)(*Address / Sector_Size)) * Sector_Size;
		printf("\nSelected Sector is %d for Erase\n", sector_address);
	}
	else	return (Address_Out_of_Range);

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

	vuint32_t sector_address = 0;
	if((*Address >= Flash_Memory_Lower_Limit) && (*Address <= Flash_Memory_Upper_Limit))
	{
		//Calculating sector starting address from provided longword address
		//It is done by converting float to integer and getting rid of
		//numbers after decimal point. For example, for the address of 2100
		//it will first do the 2100/1024, which will return 2.<some_numbers>
		//but since the result is cast as unsigned char, it will only store 2
		//Then 2 is multiplied by 1024, which is the starting address of
		//the sector in which 2100 lies
		sector_address = ((uint8_t)(*Address / Sector_Size)) * Sector_Size;
		printf("\nSelected Sector is %d for Erase Verification\n", sector_address);
	}
	else	return (Address_Out_of_Range);

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
	if(Flash_Longword_Write_Address_Alignment(*Address))	\
			return (Flash_Program_Longword_Address_Alignment_Error);

	//Checking whether the address is in limit or not
	if((*Address < Flash_Memory_Lower_Limit) || (*Address >= Flash_Memory_Upper_Limit))		\
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
					(vuint8_t)(GET_BIT_16_23(*Address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15(*Address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7(*Address)));

	//Writing Data
	//Writing MSB Byte (0xFF00_0000) to FCCOB4
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB4_Address), \
					(vuint8_t)(GET_BIT_0_7(Data)));

	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB5
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB5_Address), \
					(vuint8_t)(GET_BIT_8_15(Data)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB6
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB6_Address), \
					(vuint8_t)(GET_BIT_16_23(Data)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB7
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB7_Address), \
					(vuint8_t)(GET_BIT_24_31(Data)));

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
	if(Flash_Longword_Write_Address_Alignment(*Address))	\
			return (Flash_Program_Longword_Address_Alignment_Error);

	//Checking whether the address is in limit or not
	if((*Address < Flash_Memory_Lower_Limit) || (*Address >= Flash_Memory_Upper_Limit))	\
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
					(vuint8_t)(GET_BIT_16_23(*Address)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOB2
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB2_Address), \
					(vuint8_t)(GET_BIT_8_15(*Address)));

	//Writing LSB Byte (0x0000_00FF) to FCCOB3
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB3_Address), \
					(vuint8_t)(GET_BIT_0_7(*Address)));

	//Writing Margin Level
	//Using user margin to ensure that normal margin won't have any problems at all
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB4_Address), \
					(vuint8_t)(vuint8_t)User_Margin);

	//Writing Data
	//Writing MSB Byte (0xFF00_0000) to FCCOB8
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB8_Address), \
					(vuint8_t)(GET_BIT_0_7(Data)));

	//Writing MSB - 1 Byte (0x00FF_0000) to FCCOB9
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOB9_Address), \
					(vuint8_t)(GET_BIT_8_15(Data)));

	//Writing LSB + 1 Byte (0x0000_FF00) to FCCOBA
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOBA_Address), \
					(vuint8_t)(GET_BIT_16_23(Data)));

	//Writing LSB Byte (0x0000_00FF) to FCCOBB
	REG_WRITE((FTFA_Address_Offset + FTFA_FCCOBB_Address), \
					(vuint8_t)(GET_BIT_24_31(Data)));

	//Launching command and waiting for it to finish
	Flash_Execute_Command();
	Flash_Wait_for_CCIF();

	//Errors - if any - generated by this command
	error = No_Error;
	error = Flash_Check_for_Error();
	return (error);
}

//Flash initialization Function
void Flash_Init(void)
{
	//Clearing all errors first
	Flash_Clear_all_Errors();

	//Printing some useful information
	printf("Flash Longword Write Test\n");
	printf("Programmable Flash Address Rang: from %x \t to %x\n", Flash_Memory_Lower_Limit, Flash_Memory_Upper_Limit);
	printf("Access outside this range is forbidden\n");

	//Initializing global variables and pointer
	Flash_Data = Flash_Data_to_Write;
	Flash_Address = Flash_Address_to_Write;
	Flash_Address_Pointer = &Flash_Address;
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

//Main Function which uses all 4 - Erase, Read 1s, Write, Check
int8_t Flash_Program(vuint32_t *Address, vuint32_t Data)
{
	//Checking for Null Pointer
	if(Address == 0)	return (Null_Pointer);

	//Useful printing
	printf("The data to be written at address %x is %x\n", *Address, Data);
	printf("\nStarting Operation\n");

	//Variable to relay the returns
	int8_t return_value;

	return_value = Flash_Sector_Erase(Address);
	if(return_value != No_Error)
	{
		printf("Erase Returned with the following error:\n");
		return (return_value);
	}
	printf("\nSector Erased Successfully\n");

	return_value = Flash_Sector_Verify(Address);
	if(return_value != No_Error)
	{
		printf("Erase Verification Returned with the following error:\n");
		return (return_value);
	}
	printf("\nSector Erase Verified Successfully\n");

	return_value = Flash_Longword_Write(Address, Data);
	if(return_value != No_Error)
	{
		printf("Flash Longword Write Returned with the following error:\n");
		return (return_value);
	}
	printf("\nLongword written Successfully\n");

	return_value = Flash_Longword_Verify(Address, Data);
	if(return_value != No_Error)
	{
		printf("Flash Longword Verified Returned with the following error:\n");
		return (return_value);
	}
	printf("\nLongword verified Successfully\n");

	return (No_Error);
}

//Main
int main(void)
{
	Flash_Init();
	int8_t Flash_Program_Return;
	Flash_Program_Return = Flash_Program(Flash_Address_Pointer, Flash_Data);
	if(Flash_Program_Return != No_Error)
	{
		printf("\n\nFlash Programming Failed\n");
		Flash_Error_Handler(Flash_Program_Return);
	}
	else
	{
		printf("\n\nFlash Programming was executed Successfully\n");
	}
	printf("\nExit or Restart Now\n");
	while(1);
}











////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
