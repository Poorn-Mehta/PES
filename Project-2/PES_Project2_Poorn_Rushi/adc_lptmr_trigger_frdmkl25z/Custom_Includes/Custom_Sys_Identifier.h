/*
 * Custom_Sys_Identifier.h
 *
 *  Created on: Nov 14, 2018
 *      Author: Poorn Mehta and Rushi James Macwan
 */

#ifndef __CUSTOM_SYS_IDENTIFIER_H__
#define __CUSTOM_SYS_IDENTIFIER_H__

/*
 * This header file decides if the device being targeted is a host machine or an embedded system.
 * It will check if the target is Linux, Windows, or a Mac. Else, it is an embedded system.
 * It will then adjust the code accordingly.
 *

 */

/* Compiler flag */
#define TARGET_DEVICE (__linux__ || _WIN64 || __APPLE__ )
#if TARGET_DEVICE
    #define HOST
#else
    #define FRDM
#endif

#ifdef	HOST
	#define Output_String	printf
	#define Input_String	fgets
	typedef uint64_t	ptr_type;
	#define exit_function	system_exit
	#define Enter_Detected	'\n'
#else
	#define Output_String	Custom_UART0_Tx_String
	#define Input_String	FGETS
	typedef volatile uint32_t	ptr_type;
	#define exit_function	embedded_exit
	#define Enter_Detected	0x0D
#endif


#endif /* CUSTOM_SYSTEM_IDENTIFIER_H_ */
