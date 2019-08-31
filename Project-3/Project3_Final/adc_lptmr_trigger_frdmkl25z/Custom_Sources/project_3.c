/*
 * project_3.c
 *
 *  Created on: Dec 8, 2018
 *      Author: poorn
 */

#include "project_3.h"

uint16_t *DMA_Buffer, *DMA_Buffer2;
uint16_t *var_ptr;
uint8_t ready, buff;


void Custom_ADC_Init(void)
{
	// Enable clocks
	Enable_ADC_Clk();
	Enable_PortB_Clk();

	// Calibrate ADC
	if(Custom_ADC_Calibration())	Output_String("ADC Calibration Failed\n");
	else	Output_String("ADC Calibration Succeed\n");

	//16 bit mode, bus clock as input, divide by 2
	Configure_CFG1();

	//Route ADC sample values to DMA
	Configure_ADC_DMA();

	//Reset this register because it was set in calibration
	ADC0_SC3 = 0;

	Enable_Continuous_Mode();

	//Differential input ADC
	Enable_Differential_Mode();

	//Don't start ADC until entire init has been completed
	Disable_ADC();

	//Setting for a GPIO pin used to measure frequency
	PORTB->PCR[0] |= PORT_PCR_MUX(1);
	PTB->PDDR |= (1 << 0);
}


int Custom_ADC_Calibration(void)
{
	//16 bit mode, bus clock as input, divide by 2
	Configure_CFG1();

	//Enable hardware average, 32 samples, start calibration
	Configure_Average();

	//While loop till calibration ends
	Wait_for_Cailbration();

	if(Calibration_Status())	return 1;

	uint16_t adc_cal;// calibration variable
	adc_cal = (ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 + ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0) >> 1;
	adc_cal |= 0x8000;
	ADC0_PG = adc_cal;

	adc_cal = (ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 + ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0) >> 1;
	adc_cal |= 0x8000;
	ADC0_MG = adc_cal;

	return 0;
}

int16_t Custom_ADC_Read(uint8_t chnl)
{
	// Write to SC1A to start conversion
	ADC0_SC1A = (chnl & ADC_SC1_ADCH_MASK) |
				(ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK));
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	 // Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	return ADC0_RA;
}

// DMA

void Custom_DMA_Init(void)
{
	//Not ready
	ready = 0;
	buff = 0;

	//Aligned Allocation of 2 buffers(128 bytes alignment, 64 blocks)
	DMA_Buffer = (uint16_t*) memalign((ADC_Bytes_per_Sample * ADC_Block_Size), ADC_Block_Size);
	if(DMA_Buffer == 0)		Output_String("Buffer1 Malloc Failure");
	DMA_Buffer2 = (uint16_t*) memalign((ADC_Bytes_per_Sample * ADC_Block_Size), ADC_Block_Size);
	if(DMA_Buffer2 == 0)		Output_String("Buffer1 Malloc Failure");

	// Enable clocks
	Enable_DMA_MUX_Clk();
	Enable_DMA_Clk();

	// Disable DMA Mux channel
	Disable_DMA_Mux_Ch();


	// Configure DMA - ADC_RA is source, Aligned Allocated buffer is destination, BCR is 128 bytes
	Set_DMA_Source_Addr(&ADC0_RA);
	Set_DMA_Destination_Addr(DMA_Buffer);
	Set_BCR((ADC_Bytes_per_Sample * ADC_Block_Size));

	//Enable Interrupt, Peripheral Request, Source and Destination size to 16 butes, Auto Increment in Destination, 128byte Circular buffer
	Set_DMA_DCR();

	// Enable DMA channel and source as ADC0
	Set_Enable_DMA_Channel();

	// Enable interrupt
	NVIC_EnableIRQ(DMA0_IRQn);
}

/*
 * Handles DMA0 interrupt
 * Resets the BCR register and clears the DONE flag
 * */
void DMA0_IRQHandler(void)
{
	//Pin toggling to see a pulse everytime this ISR is called
	PTB->PDOR |= (1 << 0);

	//Clearing DONE flag
	Clear_DMA_DONE();

	//Setting BCR again
	Set_BCR((ADC_Bytes_per_Sample * ADC_Block_Size));
	PTB->PDOR &= ~(1 << 0);

	//Using one buffer after another
	if(buff == 0)
	{
		Set_DMA_Destination_Addr(DMA_Buffer2);
		buff = 1;
	}
	else
	{
		Set_DMA_Destination_Addr(DMA_Buffer);
		buff = 0;
	}

	//Signal to main loop
	ready += 1;
}



// PIT
void pit_init(void)
{
	// Enable PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	// Turn on PIT
	PIT_MCR = 0;

	// Configure PIT to produce an interrupt every 1s
//	PIT_LDVAL0 = 0x1312CFF;	// 1/20Mhz = 50ns   (1s/50ns)-1= 19,999,999 cycles or 0x1312CFF
	PIT_LDVAL0 = ((0x1312CFF)/(64*2));
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; // Enable interrupt and enable timer

	// Enable interrupt registers ISER and ICPR
	NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void)
{
	// Clear interrupt
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;

	// Write to SC1A to start conversion
	ADC0_SC1A = (ADC_SC1_ADCH(ADC_Channel) |
				 (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));
}

