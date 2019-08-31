/*
 * Custom_UART.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Poorn Mehta and Rushi James Macwan
 */

#include "Custom_UART.h"
#include "Custom_Circular_Buffer.h"
volatile Byte UART0_Byte;
UART0_Operation_Type State = Normal_Operation;

volatile Byte isr_arr[50], isr_cnt = 0;
Byte led;

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

	//Addition steps for interrupt mode
	#ifdef	INTERRUPT_MODE
		Enable_Rx_Interrupt();
		NVIC_EnableIRQ(UART0_IRQn);
	#endif

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

    //For interrupt mode, set a array which is shared between ISR and this function
    //Cleaning up that array here
	#ifdef	INTERRUPT_MODE
    while(isr_cnt != 0);
	for(uart_i = 0; uart_i < 50; uart_i ++)		isr_arr[uart_i] = 0;
	#endif
	//Acutally setting up array
    for(uart_i = 0; uart_i < string_length; uart_i ++)
    {
    	//Calling polling transmit byte function repeatedly
		#ifdef 	POLLING_MODE
    	Custom_UART0_Tx_Byte(array[uart_i]);
		#else
    	//Filling data in shared array
    	isr_arr[uart_i] = array[uart_i];
		#endif
    }
    //Enable transmitter buffer empty interrupt
    //It should be kept disable normally to avoid going into ISR infinitely, continuously, and instantly
	#ifdef	INTERRUPT_MODE
    Enable_TxE_Interrupt();
	#endif
}

//Polling function to receive a byte
void Custom_UART0_Rx_Byte(volatile Byte *address)
{
	//Polling flag to see if any data has been received
	UART0_Wait_for_Rx_Data_Register();

	//Storing that byte using the pointer of the variable
	UART0_Rx_Data(address);
}

void UART0_IRQHandler(void)
{
	//Check whether Rx interrupt has caused the code to go in ISR or Tx empty interrupt
    if(UART0_Rx_Interrupt())
    {
    	//First store the byte in a variable
    	UART0_Rx_Data(&UART0_Byte);

#if		APPLICATION

    	//To see whether it's FGETS running or normal one
    	if(State == Normal_Operation)
		{
    		//Write byte in the UART Rx circular buffer
    		CBuffer_Byte_Write(UART0_Rx_Buffer_ID, UART0_Byte);

    		//Code for fun :P
        	if(led < 7)		led += 1;
        	else	led = 0;
		}
    	else if(State == FGETS_Operation)
		{
    		//Echo byte to actually see what's being typed in
    		UART0_Tx_Data(UART0_Byte);

    		//Write byte in FGETS circular buffer
    		CBuffer_Byte_Write(FGETS_Buffer_ID, UART0_Byte);

    		//Leave FGETS function is the user presses enter or the buffer is filled up
    		if((CBuffer_Instance[FGETS_Buffer_ID].Status == Full) || (Enter_Detected == UART0_Byte))	State = Normal_Operation;
		}

#else
    	UART0_Tx_Data(UART0_Byte);
#endif

    }
    else if(UART0_TxE_Interrupt())
    {
    	//Transmit one byte if the index in shared array hasn't reached null
    	if(isr_arr[isr_cnt] != 0)	UART0_Tx_Data(isr_arr[isr_cnt ++]);

    	//If the index is pointing to null then reset index, and disable Tx empty interrupt
    	else
		{
    		Disable_TxE_Interrupt();
    		isr_cnt = 0;
		}
    }
}
