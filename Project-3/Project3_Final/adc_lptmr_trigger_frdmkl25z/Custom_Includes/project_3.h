/*
 * project_3.h
 *
 *  Created on: Dec 8, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_INCLUDES_PROJECT_3_H_
#define CUSTOM_INCLUDES_PROJECT_3_H_

#include "Custom_Main.h"
#include "Custom_UART.h"

/* Prototypes */
void Custom_ADC_Init(void);
int Custom_ADC_Calibration(void);
int16_t Custom_ADC_Read(uint8_t chnl);

// DMA

#define  ADC_Block_Size			64
#define  ADC_Bytes_per_Sample	2
#define ADC_Channel 			0

#define Enable_ADC_Clk()		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK
#define Enable_PortB_Clk()		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK

#define Configure_CFG1()		ADC0_CFG1 = (ADC_CFG1_MODE(3)  | ADC_CFG1_ADICLK(0)| ADC_CFG1_ADIV(1))

#define Configure_Average()		ADC0_SC3 = (ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) | ADC_SC3_CAL_MASK)

#define Wait_for_Cailbration()	while(ADC0_SC3 & ADC_SC3_CAL_MASK)

#define Calibration_Status()		ADC0_SC3 & ADC_SC3_CALF_MASK

#define Configure_ADC_DMA()		ADC0_SC2 |= ADC_SC2_DMAEN_MASK

#define Enable_Continuous_Mode()	ADC0_SC3 |= ADC_SC3_ADCO(1)

#define Enable_Differential_Mode()	ADC0_SC1A |= ADC_SC1_DIFF_MASK

#define Disable_ADC()				ADC0_SC1A |= ADC_SC1_ADCH(31)

#define Enable_ADC()				ADC0_SC1A = (ADC_SC1_ADCH(ADC_Channel) | (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)))

void Custom_DMA_Init(void);
void DMA0_IRQHandler(void);

#define Enable_DMA_MUX_Clk()		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK

#define Enable_DMA_Clk()			SIM_SCGC7 |= SIM_SCGC7_DMA_MASK

#define Disable_DMA_Mux_Ch()		DMAMUX0_CHCFG0 = 0x00

#define Set_DMA_Source_Addr(addr)		DMA_SAR0 = (uint32_t)addr

#define Set_DMA_Destination_Addr(addr)	DMA_DAR0 = (uint32_t)addr

#define Set_BCR(x)						DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(x)

#define Set_DMA_DCR()					DMA_DCR0 |= (DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK | \
											DMA_DCR_SSIZE(2) | DMA_DCR_DINC_MASK| DMA_DCR_DMOD(4) | DMA_DCR_DSIZE(2))

#define Set_Enable_DMA_Channel()		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(40)

#define Clear_DMA_DONE()				DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK


// PIT


void pit_init(void);
void PIT_IRQHandler(void);

#endif /* CUSTOM_INCLUDES_PROJECT_3_H_ */
