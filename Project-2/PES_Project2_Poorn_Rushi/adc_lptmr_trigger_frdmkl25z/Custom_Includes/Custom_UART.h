/*
 * Custom_UART.h
 *
 *  Created on: Nov 14, 2018
 *      Author: Poorn Mehta and Rushi James Macwan
 */

#ifndef CUSTOM_INCLUDES_CUSTOM_UART_H_
#define CUSTOM_INCLUDES_CUSTOM_UART_H_

#include "Custom_Main.h"

//Defines and conditions for switching between polling and interrupt mode
#define POLLING		0
#define INTERRUPT	1

#define UART_MODE	INTERRUPT

#if UART_MODE
	#define INTERRUPT_MODE
	#define	APPLICATION		1
#else
	#define POLLING_MODE
#endif

//Defines for clocking UART
#define Clock_Gating_Register_4		SCGC4
#define System_Integration_Module	SIM
#define UART0_Clock_Gate_Bit			10
#define Enable_UART0_Clock()		(System_Integration_Module->Clock_Gating_Register_4 |= (1 << UART0_Clock_Gate_Bit))

//Define for function selection
#define UART0_Port		PORTA
#define Pin_Control_Register	PCR
#define UART0_Rx_Pin		1
#define UART0_Tx_Pin		2
#define UART0_Function	0x02	//page 162 in ref manual
#define Pin_Function_Select(x)		PORT_PCR_MUX(x)

//Macros for function select
#define Enable_UART0_Rx_Function()		(UART0_Port->Pin_Control_Register[UART0_Rx_Pin] |= \
											Pin_Function_Select(UART0_Function))
#define Enable_UART0_Tx_Function()		(UART0_Port->Pin_Control_Register[UART0_Tx_Pin] |= \
											Pin_Function_Select(UART0_Function))

//Defines for UART Interrupt configuration
#define UART0_TxE_Interrupt_Bit			7
#define UART0_Rx_Interrupt_Bit			5
#define UART0_Transmitter_Enable_Bit	3
#define UART0_Receiver_Enable_Bit		2
#define UART0_Control_Register_2		C2
#define UART0_Register_Handler			UART0

//Macros for UART Interrupt support
#define Disable_UART0_Tx()				(UART0_Register_Handler->UART0_Control_Register_2 &= \
											~(1 << UART0_Transmitter_Enable_Bit))
#define Disable_UART0_Rx()				(UART0_Register_Handler->UART0_Control_Register_2 &= \
											~(1 << UART0_Receiver_Enable_Bit))
#define Enable_UART0_Tx()				(UART0_Register_Handler->UART0_Control_Register_2 |= \
											(1 << UART0_Transmitter_Enable_Bit))
#define Enable_UART0_Rx()				(UART0_Register_Handler->UART0_Control_Register_2 |= \
											(1 << UART0_Receiver_Enable_Bit))
#define Enable_Rx_Interrupt()			(UART0_Register_Handler->UART0_Control_Register_2 |= \
											(1 << UART0_Rx_Interrupt_Bit))
#define Enable_TxE_Interrupt()			(UART0_Register_Handler->UART0_Control_Register_2 |= \
											(1 << UART0_TxE_Interrupt_Bit))
#define Disable_TxE_Interrupt()			(UART0_Register_Handler->UART0_Control_Register_2 &= \
											~(1 << UART0_TxE_Interrupt_Bit))

//Defines and macros for clock source selection and configuration for UART
#define System_Option_Register_2		SOPT2
#define	PLL_FLL_Clock_Select_Bit		16
#define Select_PLL_Clock_Divby2()		(System_Integration_Module->System_Option_Register_2 |= \
											(1 << PLL_FLL_Clock_Select_Bit))
#define Select_FLL_Clock()				(System_Integration_Module->System_Option_Register_2 &= \
											~(1 << PLL_FLL_Clock_Select_Bit))
#define UART0_Clock_Source_Offset		26
#define UART0_Clock_Souce_FLL_PLL		1
#define UART0_FLL_PLL_Clock_Source()	(System_Integration_Module->System_Option_Register_2 |= \
											(UART0_Clock_Souce_FLL_PLL << UART0_Clock_Source_Offset))

//Defines and macros for BAUD rate
#define BAUD_Rate		115200UL
#define System_Clock	48000000UL
#define Oversampling	16
#define BAUD_Rate_Setting_Value		(Word)(System_Clock / (BAUD_Rate * Oversampling))
#define BAUD_Rate_High_Mask			0x1F00
#define BAUD_Rate_Low_Mask			0x00FF
#define BAUD_Rate_High_Register		BDH
#define BAUD_Rate_Low_Register		BDL
#define Set_BAUD_Rate_High_Register()		(UART0_Register_Handler->BAUD_Rate_High_Register = \
												(BAUD_Rate_Setting_Value & BAUD_Rate_High_Mask))
#define Set_BAUD_Rate_Low_Register()		(UART0_Register_Handler->BAUD_Rate_Low_Register = \
												(BAUD_Rate_Setting_Value & BAUD_Rate_Low_Mask))

//Defines and macros for oversampling
#define UART0_Control_Register_4		C4
#define Oversampling_16					0x0F
#define Set_Oversampling()				(UART0_Register_Handler->UART0_Control_Register_4 = \
												Oversampling_16)

//Defines and macros for polling UART functions
#define UART0_Status_Register_1				S1
#define Tx_Data_Register_Empty_Flag_Bit		7	//1 means empty
#define Tx_Data_Transmission_Complete_Flag_Bit	6	//1 means complete
#define UART0_Tx_Empty_Flag_Status()		((UART0_Register_Handler->UART0_Status_Register_1) & \
												(1 << Tx_Data_Register_Empty_Flag_Bit))
#define UART0_Wait_for_Tx_Data_Register()	while((!UART0_Tx_Empty_Flag_Status()))

#define Rx_Data_Register_Full_Flag_Bit		5	//1 means full
#define UART0_Wait_for_Rx_Data_Register()	while(!((UART0_Register_Handler->UART0_Status_Register_1) & \
												(1 << Rx_Data_Register_Full_Flag_Bit)))

//Defines and macros for interrupt UART functions
#define UART0_Data_Register				D
#define UART0_Tx_Data(x)				(UART0_Register_Handler->UART0_Data_Register = x)
#define UART0_Rx_Data(addr)				(*addr = UART0_Register_Handler->UART0_Data_Register)

#define UART0_Rx_Interrupt()			(UART0_Register_Handler->UART0_Status_Register_1 & \
											(1 << Rx_Data_Register_Full_Flag_Bit))

#define UART0_TxE_Interrupt()			(UART0_Register_Handler->UART0_Status_Register_1 & \
											(1 << Tx_Data_Register_Empty_Flag_Bit))

//Currently only 2 modes - can be increased easily in future
typedef enum
{
	FGETS_Operation,
	Normal_Operation
}UART0_Operation_Type;

//Function initializations
void Custom_UART0_Init(void);
void ASCII_Counter2(void);
void Custom_UART0_Tx_Byte(Byte data);
void Custom_UART0_Tx_String(char *array);
void Custom_UART0_Rx_Byte(volatile Byte *address);
void UART0_IRQHandler(void);

//Variables
extern UART0_Operation_Type State;
extern volatile Byte UART0_Byte;

#endif /* CUSTOM_INCLUDES_CUSTOM_UART_H_ */
