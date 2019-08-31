/*
 * custom_system_identifier.h
 *
 *  Created on: Nov 2, 2018
 *      Author: poorn
 */

/*
 * This header file decides if the device being targeted is a host machine or an embedded system.
 * It will check if the target is Linux, Windows, or a Mac. Else, it is an embedded system.
 * It will then adjust the code accordingly.
 *

 */

#ifndef CUSTOM_SYSTEM_IDENTIFIER_H_
#define CUSTOM_SYSTEM_IDENTIFIER_H_

/* Compiler flag */
#define TARGET_DEVICE (__linux__ || _WIN64 || __APPLE__ )
#if TARGET_DEVICE
    #define HOST
#else
    #define FRDM
#endif

#ifdef	HOST
	#define output_string	printf
	#define input_string	fgets
	#define start_timing	clkbegin
	#define stop_timing		clkend
	typedef uint64_t	ptr_type;
	#define exit_function	system_exit
	#define Enter_Detected	'\n'
#else
	#define output_string	PRINTF
	#define input_string	FGETS
	#define start_timing	Timer_Start
	#define stop_timing		Timer_Stop
	typedef volatile uint32_t	ptr_type;
	#define exit_function	embedded_exit
	#define Enter_Detected	0x0D
#endif

#endif /* CUSTOM_SYSTEM_IDENTIFIER_H_ */
