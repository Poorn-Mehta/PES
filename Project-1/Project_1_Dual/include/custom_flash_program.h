/*
 * custom_flash_program.h
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */
#ifdef FRDM

#ifndef CUSTOM_FLASH_PROGRAM_H_
#define CUSTOM_FLASH_PROGRAM_H_

#include "custom_main.h"

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
const char Access_Error_String[] = "\n\rExecuted Command was unable to Access Flash\n\r";
const char Read_Collision_Error_String[] = "\n\rMCU Attempted Read while Flash Command was Running\n\r";
const char Flash_Protection_Violation_String[] = "\n\rExecuted Command at provided Flash Address\n\rdetected flash protection violation\n\r";
const char Run_Time_Error_String[] = "\n\rExecuted Command ran into Run Time Error\n\r";
const char All_Errors_String[] = "\n\rCongratulations :D You ran into ALL of the ERRORS\n\r";
const char Unknown_Error_String[] = "\n\rWho knows what happened :/\n\r\n\rBetter luck next time :P\n\r";
const char Address_out_of_Range_Error_String[] = "\n\rProvided Flash Address is Out of Range\n\r";
const char Address_Alignment_Error_String[] = "\n\rProvided Flash Address is not aligning with Longword Access\n\r";
const char Null_Pointer_Error_String[] = "\n\rNull Pointer Passed\n\r";

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



//Access Error
void Access_Error_Print(void);
void Read_Collision_Error_Print(void);
void Flash_Protection_Violation_Error_Print(void);
void Run_Time_Error_Print(void);
void Access_and_Collision_Error_Print(void);
void Access_and_Violation_Error_Print(void);
void Access_and_Run_Error_Print(void);
void Collision_and_Violation_Error_Print(void);
void Collision_and_Run_Error_Print(void);
void Violation_and_Run_Error_Print(void);
void Access_and_Collision_and_Violation_Error_Print(void);
void Access_and_Collision_and_Run_Error_Print(void);
void Access_and_Violation_and_Run_Error_Print(void);
void Collision_and_Violation_and_Run_Error_Print(void);
void All_Errors_Print(void);
void Unknown_Error_Print(void);
void Address_out_of_Range_Error_Print(void);
void Address_Alignment_Error_Print(void);
void Null_Pointer_Error_Print(void);

void Flash_Sector_Read_Write_Sequence(vuint32_t *Address, vuint32_t Data);
int8_t Flash_Sector_Erase(vuint32_t *Address);
int8_t Flash_Sector_Verify(vuint32_t *Address);
int8_t Flash_Longword_Write(vuint32_t *Address, vuint32_t Data);
int8_t Flash_Longword_Verify(vuint32_t *Address, vuint32_t Data);
void Flash_Error_Handler(int8_t Error_Code);
int8_t Flash_Program(vuint32_t *Address, vuint32_t Data);

int8_t test(vuint32_t *Address);

extern vuint32_t Flash_Data, Flash_Address, *Flash_Address_Pointer, *Flash_Buffer_Pointer;
extern vuint32_t Buffer[256];
extern volatile uint16_t flash_i;
extern vuint32_t sector_address;

#endif /* CUSTOM_FLASH_PROGRAM_H_ */

#endif
