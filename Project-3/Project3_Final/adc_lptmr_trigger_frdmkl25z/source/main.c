/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

// Standard C Included Files
#include <string.h>
#include <stdio.h>
// SDK Included Files

#include "board.h"
#include "pin_mux.h"
#include "fsl_clock_manager.h"

#include "fsl_debug_console.h"
//#include "adc_hw_trigger.h"
//#include "fsl_adc16_driver.h"

uint16_t *DMA_Buffer = NULL;
uint16_t *DMA_Buffer2 = NULL;
uint16_t *var_ptr = NULL;
uint32_t volt = 0;
uint8_t ready = 0;
uint8_t buff = 0;

#define Decay	0.99

#include "Custom_Main.h"
#include "Custom_UART.h"
#include "project_3.h"


int main (void)
{
	//Init hardware
	hardware_init();

	char adc_str[30];
	uint32_t i;
	int32_t	avg;
	avg = 0;
	ready = 0;
	int32_t peak1 = 0;
	uint32_t peak_volt = 0;
	volatile uint32_t peak2 = 0;
	volatile uint32_t pre_peak = 0;

	Custom_UART0_Init();
	Custom_DMA_Init();
	Custom_ADC_Init();
//	pit_init();	//Can be used to slow down ADC and watch its exact behavior


	Output_String("Program Start\n\r");

	Enable_ADC();

//	ADC0_SC1A = (ADC_SC1_ADCH(ADC_Channel) |
//				 (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));


	while(1)
	{
		if(ready > 0)	//Is new data availalbe?
		{
//			ADC0_SC1A |= ADC_SC1_ADCH(31); // Disable module

			if(buff == 0)	var_ptr = DMA_Buffer;
			else	var_ptr = DMA_Buffer2;
			//Average calculation, Peak calculation, peak of buffer = peak2, each sample = peak1
			for(i = 0; i < ADC_Block_Size; i++, var_ptr++)
			{
//				sprintf(adc_str, "ADC_val %d : %d\n\r", i, (int16_t)*var_ptr);
//				Output_String(adc_str);
				peak1 = (int16_t)*var_ptr;
				if(peak1 < 0)	peak1 *= -1;
				if(peak1 > peak2)	peak2 = peak1;
				avg += (int16_t)*var_ptr;
			}

//			if(buff == 0)	var_ptr = DMA_Buffer;
//			else	var_ptr = DMA_Buffer2;

			//Average and voltage calculation
			avg /= ADC_Block_Size;
			volt = ((avg * 3300) / 32767);

			//Either Decay or Peak Update
			if(pre_peak > peak2)
			{
				pre_peak *= Decay;
				peak_volt = ((pre_peak * 3300) / 32767);
				sprintf(adc_str, "ADC avg milliVolts: %d   ADC Peak: %d  Peak mV: %d\n", volt, pre_peak, peak_volt);
				Output_String(adc_str);
			}
			else
			{
				pre_peak = peak2;
				peak_volt = ((peak2 * 3300) / 32767);
				sprintf(adc_str, "ADC avg milliVolts: %d   ADC Peak: %d  Peak mV: %d\n", volt, peak2, peak_volt);
				Output_String(adc_str);
			}

			//Resetting variables
			peak2 = 0;
			avg = 0;
			ready = 0;

//			ADC0_SC1A = (ADC_SC1_ADCH(ADC_Channel) |
//						 (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
//// Definitions
/////////////////////////////////////////////////////////////////////////////////
//
//#define ADC_12BIT_MAXVALUE (0x1000U)
//#define RATIO (ADC_12BIT_MAXVALUE/CHART_ROWS)
//
///*! @brief Define the sparse matrix node for display wave */
//#pragma pack(1)
//typedef struct sparse_node
//{
//    struct sparse_node *next; /*!< next node */
//    uint8_t value; /*!< the sample index */
//
//} sparse_node_t, *sparse_node_ptr;
//#pragma pack()
//
/////////////////////////////////////////////////////////////////////////////////
//// Prototypes
/////////////////////////////////////////////////////////////////////////////////
//
//extern void init_trigger_source(uint32_t instance);
//extern void deinit_trigger_source(uint32_t instance);
//
//#ifdef USE_DAC_OUT_AS_SOURCE
//extern void dac_gen_wave(void);
//extern void dac_stop_wave(void);
//#endif
//
//extern void ADC_TEST_InstallCallback(uint32_t instance, uint32_t chnGroup, void (*callbackFunc)(void) );
//extern uint16_t ADC_TEST_GetConvValueRAWInt(uint32_t instance, uint32_t chnGroup);
//
/////////////////////////////////////////////////////////////////////////////////
//// Variables
/////////////////////////////////////////////////////////////////////////////////
//
//SIM_Type * gSimBase[] = SIM_BASE_PTRS; // SIM base address
//static volatile bool gAdcDone = false; // sync object for adc convert result
//static sparse_node_ptr gChartHead[CHART_ROWS]; // sparse matrix head
//static sparse_node_t gChartNodes[NR_SAMPLES]; // sparse matrix nodes
//static uint32_t gFreeNode = 0; // free node slot index for gChartNodes[]
//static volatile uint8_t gCurChan = 0;
//
/////////////////////////////////////////////////////////////////////////////////
//// Code
/////////////////////////////////////////////////////////////////////////////////
//
///*!
// * @brief ADC channel0 callback for fetching sample data.
// */
//static void adc_chn0_isr_callback(void)
//{
//    gCurChan = 0;
//    gAdcDone = true;
//}
//
///*!
// * @brief ADC channel1 callback for fetching sample data.
// */
//static void adc_chn1_isr_callback(void)
//{
//    gCurChan = 1;
//    gAdcDone = true;
//}
//
///*!
// * @brief Initialize the ADCx for HW trigger.
// *
// * @param instance The ADC instance number
// */
//static int32_t init_adc(uint32_t instance)
//{
//    adc16_converter_config_t adcUserConfig;
//    adc16_chn_config_t adcChnConfig;
//#if FSL_FEATURE_ADC16_HAS_CALIBRATION
//    // Initialization ADC for calibration purposes
//    adc16_calibration_param_t adcCalibrationParam;
//    adc16_chn_config_t adcCalibrationChnConfig;
//    const adc16_hw_average_config_t adcAverageConfig = {
//      .hwAverageEnable = true,
//      .hwAverageCountMode = kAdc16HwAverageCountOf32
//    };
//
//    ADC16_DRV_StructInitUserConfigDefault(&adcUserConfig);
//#if BOARD_ADC_USE_ALT_VREF
//    adcUserConfig.refVoltSrc = kAdc16RefVoltSrcOfValt;
//#endif
//    ADC16_DRV_Init(instance, &adcUserConfig);
//    ADC16_DRV_ConfigHwAverage(instance, &adcAverageConfig);
//
//    adcChnConfig.chnIdx = kAdc16Chn31;
//#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
//    adcCalibrationChnConfig.diffConvEnable = false;
//#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
//    adcCalibrationChnConfig.convCompletedIntEnable = false;
//
//    // Configure channel0
//    ADC16_DRV_ConfigConvChn(instance, 0U, &adcCalibrationChnConfig);
//
//    // Configure channel1, which is used in PDB trigger case
//    ADC16_DRV_ConfigConvChn(instance, 1U, &adcCalibrationChnConfig);
//
//    // Auto calibration.
//    ADC16_DRV_GetAutoCalibrationParam(instance, &adcCalibrationParam);
//    ADC16_DRV_SetCalibrationParam(instance, &adcCalibrationParam);
//#endif
//
//    // Initialization ADC for
//    // 12bit resolution, interrrupt mode, hw trigger enabled.
//    // normal convert speed, VREFH/L as reference,
//    // disable continuouse convert mode.
//    ADC16_DRV_StructInitUserConfigDefault(&adcUserConfig);
//    adcUserConfig.hwTriggerEnable = true;
//    adcUserConfig.continuousConvEnable = false;
//#if BOARD_ADC_USE_ALT_VREF
//    adcUserConfig.refVoltSrc = kAdc16RefVoltSrcOfValt;
//#endif
//    ADC16_DRV_Init(instance, &adcUserConfig);
//
//    // Install Callback function into ISR
//    ADC_TEST_InstallCallback(instance, 0U, adc_chn0_isr_callback);
//    ADC_TEST_InstallCallback(instance, 1U, adc_chn1_isr_callback);
//
//    adcChnConfig.chnIdx = (adc16_chn_t)ADC_INPUT_CHAN;
//#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
//    adcChnConfig.diffConvEnable = false;
//#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
//    adcChnConfig.convCompletedIntEnable = true;
//
//    // Configure channel0
//    ADC16_DRV_ConfigConvChn(instance, 0U, &adcChnConfig);
//
//    // Configure channel1, which is used in PDB trigger case
//    ADC16_DRV_ConfigConvChn(instance, 1U, &adcChnConfig);
//
//    return 0;
//}
//
///*!
// * @brief Reset the sparse matrix
// */
//void sparse_reset(void)
//{
//    memset(gChartHead, 0, sizeof(gChartHead));
//    memset(gChartNodes, 0, sizeof(gChartNodes));
//    gFreeNode = 0;
//}
//
///*!
// * @brief insert a node into the sparse matrix
// *
// * @param index The amplitude index
// * @param value The sample count value
// */
//void sparse_insert(uint32_t index, uint8_t value)
//{
//    sparse_node_ptr p = gChartHead[index];
//
//    assert(gFreeNode < NR_SAMPLES);
//
//    if (!p)
//    {
//        gChartHead[index] = &gChartNodes[gFreeNode++];
//        gChartHead[index]->value = value;
//    }
//    else
//    {
//        while (p->next != NULL)
//        {
//            p = p->next;
//        }
//        p->next = &gChartNodes[gFreeNode++];
//        p->next->value = value;
//    }
//}
//
///*!
// * @brief Main demo function
// */
//int main(void)
//{
//    uint8_t cnt;
//    int32_t row;
//
//    // init the hardware board
//    hardware_init();
//
//    PRINTF("\r\nadc_hw_trigger demo running...\r\n\r\n");
//
//#ifdef USE_DAC_OUT_AS_SOURCE
//    // use DAC to generate the sine wave
//    dac_gen_wave();
//#else
//    // If no DAC can be use, then a function generator should
//    // be used to generate a signal wave, and connect to ADC input
//#endif
//
//    // initialize the ADC
//    if (init_adc(ADC_INST))
//    {
//        PRINTF("Failed to do the ADC init\r\n");
//        return -1;
//    }
//
//    // setup the HW trigger source
//    init_trigger_source(ADC_INST);
//
//    // init the print chart array
//    sparse_reset();
//
//    for (cnt = 0; cnt < NR_SAMPLES; cnt++)
//    {
//        uint16_t result;
//        double tmpRatio;
//
//        while (gAdcDone != true)
//        {
//            ;
//        }
//
//        result = ADC16_DRV_GetConvValueRAW(ADC_INST, (uint32_t)gCurChan);
//        gAdcDone = false;
//
//        // insert the sample data into the sparse matrix
//        tmpRatio = (double)result / RATIO;
//        row = (int32_t)tmpRatio;
//        if (row >= CHART_ROWS)
//        {
//            row = CHART_ROWS - 1;
//        }
//        // fill one samples into sparse matrix
//        sparse_insert(row, cnt);
//    }
//
//    // print the chart
//    for (row = CHART_ROWS - 1; row >= 0; row --)
//    {
//        sparse_node_ptr p = gChartHead[row];
//        uint32_t last = 0;
//
//        while (p)
//        {
//            for (; last < p->value; last++)
//            {
//                PRINTF(" ");
//            }
//            PRINTF("*");
//            p = p->next;
//            last++;
//        }
//        PRINTF("\r\n");
//    }
//
//    // disable the adc0
//    ADC16_DRV_Deinit(ADC_INST);
//    // disable hw trigger source
//    deinit_trigger_source(ADC_INST);
//#ifdef USE_DAC_OUT_AS_SOURCE
//    // disable dac source
//    dac_stop_wave();
//#endif
//
//    while(1)
//    {}
//}
