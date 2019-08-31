/*
 * Custom_UART.c
 *
 *  Created on: Nov 14, 2018
 *      Author: poorn
 */

#include "Custom_UART.h"

//UART0 Initialization Function
void Custom_UART0_Init(void)
{
	//Enabling clock first
	Enable_UART0_Clock();

	//Selecting proper Mux values for UART function
	Enable_UART0_Rx_Function();
	Enable_UART0_Tx_Function();

	//Disabling pins for configuring UART safely
	Disable_UART0_Tx();
	Disable_UART0_Rx();

	//Selecting and configuring clock source to drive UART
	Select_PLL_Clock_Divby2();
	UART0_FLL_PLL_Clock_Source();
	Set_BAUD_Rate_High_Register();
	Set_BAUD_Rate_Low_Register();

	//Selecting oversampling value
	Set_Oversampling();

	//Enabling pins
	Enable_UART0_Tx();
	Enable_UART0_Rx();
}

//Polling transmitting byte function
void Custom_UART0_Tx_Byte(Byte data)
{
	//Polling flag to check for availability of UART transmitter
	UART0_Wait_for_Tx_Data_Register();

	//Putting byte in buffer/data register
	UART0_Tx_Data(data);
}

//Function to transmit strings through UART
void Custom_UART0_Tx_String(char *array)
{
    DWord uart_i;
    DWord string_length = strlen(array);

	//Acutally setting up array
    for(uart_i = 0; uart_i < string_length; uart_i ++)
    {
    	//Calling polling transmit byte function repeatedly
    	Custom_UART0_Tx_Byte(array[uart_i]);
    }
}

//Polling function to receive a byte
void Custom_UART0_Rx_Byte(volatile Byte *address)
{
	//Polling flag to see if any data has been received
	UART0_Wait_for_Rx_Data_Register();

	//Storing that byte using the pointer of the variable
	UART0_Rx_Data(address);
}
