/*
 * adc.h
 *
 *  Created on: 08-Dec-2020
 *      Author: emes
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include "stm32f4.h"


typedef struct
{
	uint8_t ADC_Resolution;
	uint8_t ADC_Analog_WD_RegCh;
	uint8_t ADC_Analog_WD_InjCh;
	uint8_t ADC_Discontinuous_ChCount;
	uint8_t ADC_Discontinuous_InjCh;
	uint8_t ADC_Discontinuous_RegCh;
	uint8_t ADC_Auto_InjCh_Con;
	uint8_t ADC_WD_ScanMode;
	uint8_t ADC_ScanMode;
	uint8_t ADC_Analog_WD_ChSel;
	uint8_t ADC_Start_RegCh_Con;
	uint8_t ADC_ExternalTrig_RegCh;
	uint8_t ADC_External_RegCh_Sel;
	uint8_t ADC_Start_InjCh_Con;
	uint8_t ADC_ExternalTrig_InjCh;
	uint8_t ADC_External_InjCh_Sel;
	uint8_t ADC_DataAlignment;
	uint8_t ADC_End_Conv_Sel;
	uint8_t ADC_Continuous_Con;
	uint8_t ADC_SampleTime;
	uint8_t ADC_InjCh_DataOffset;
	uint8_t ADC_WD_HighTh;
	uint8_t ADC_WD_LowTh;
	uint8_t ADC_ON;
}ADC_Config_t;


typedef struct
{
	uint8_t Reg_Seq_Len;
	uint8_t Ch_No_Ch_Seq;
	uint8_t Inj_Seq_Len;
	uint8_t Ch_No_InjCh_Sq;
}ADC_Regular_Injected_Seq;

typedef struct
{
	ADC_RegDef_t *pADCx;
	ADC_Config_t ADC_Config_t;
	ADC_Regular_Injected_Seq ADC_Seq;
}ADC_Handle_t;



/***********************ADC CONFIG DATA MEMBER POSSIBLE VALUE*************************************/

//ADC RESOLUTION
#define ADC_RESOLUTION_12BIT		0
#define ADC_RESOLUTION_10BIT		1
#define ADC_RESOLUTION_8BIT			2
#define ADC_RESOLUTION_6BIT			3

//ADC ANALOG WATCHDOG ON REGULAR CHANNEL
#define ANALOG_WD_REGCH_DI		0
#define	ANALOG_WD_REGCH_EN		1

//ADC ANALOG WATCHDOG ON INJECTED CHANNEL
#define ANALOG_WD_INJCH_DI		0
#define ANALOG_WD_INJCH_EN		1

//ADC DISCONTINUOUS MODE CHANNEL COUNT
//Value can be 1 to 8

//ADC DISCONTINUOUS ON INJECTED CHANNEL
#define ADC_DIS_INJCH_DI		0
#define ADC_DIS_INJCH_EN		1

//ADC DISCONTINUOUS ON REGULAR CHANNEL
#define ADC_DIS_REGCH_DI		0
#define ADC_DIS_REGCH_EN		1

//ADC AUTOMATIC INJECTION
#define ADC_AUTO_INJ_DI			0
#define ADC_AUTO_INJ_EN			1

//ADC ANALOG WATCHDOG ON SINGLE CHANNEL IN SCAN MODE
#define ADC_ANALOG_WD_SCAN_SINGLE_CH_DI		0
#define ADC_ANALOG_WD_SCAN_SINGLE_CH_EN		1

//ADC SCAN MODE
#define ADC_SCAN_MODE_DI		0
#define ADC_SCAN_MODE_EN		1

//ADC ANALOG WATCHDOG CHANNEL SELECTION
//It can be any channel number

//ADC START CONVERSION OF REGULAR CHANNEL
#define ADC_REGCH_START_CON		1
#define ADC_REGCH_STOP_CON		0

//ADC EXTERNAL TRIGGER ENABLE FOR REGULAR CHANNEL AND INJECTED CHANNEL
#define ADC_TRIG_DI					0
#define ADC_TRIG_ON_RISING_EDGE		1
#define ADC_TRIG_ON_FALLING_EDGE	2
#define ADC_TRIG_ON_RIS_FAL_EDGE	3

//ADC EXTERNAL EVENT SELECTION FOR REGULAR GROUP AND INJECTED GROUP
#define TIMER1_CC1_EVENT		0
#define TIMER1_CC2_EVENT		1
#define TIMER1_CC3_EVENT		2
#define TIMER2_CC2_EVENT		3
#define TIMER2_CC3_EVENT		4
#define TIMER2_CC4_EVENT		5
#define TIMER2_TRGO_EVENT		6
#define TIMER3_CC1_EVENT		7
#define TIMER3_TRGO_EVENT		8
#define TIMER4_CC4_EVENT		9
#define TIMER5_CC1_EVENT		10
#define TIMER5_CC2_EVENT		11
#define TIMER5_CC3_EVENT		12
#define TIMER8_CC1_EVENT		13
#define TIMER8_TRGO_EVENT		14
#define EXTI_LINE11				15

//ADC START CONVERSION OF INJECTED CHANNEL
#define ADC_INJCH_START_CON		1
#define ADC_INJCH_STOP_CON		0

//ADC DATA ALIGNEMENT
#define ADC_RIGHT_ALIGN		0
#define ADC_LEFT_ALIGN		1

//ADC CONTINUOUS CONVERSION
#define SINGLE_CON_MODE				0
#define SINGLE_CONTINUOUS_CON_MODE	1

//ADC POWER MODE
#define ADC_DISABLE		0
#define ADC_ENABLE		1

//ADC SAMPLE TIME
#define ADC_SAMPLE_3_CYCLE
#define ADC_SAMPLE_15_CYCLE
#define ADC_SAMPLE_28_CYCLE
#define ADC_SAMPLE_56_CYCLE
#define ADC_SAMPLE_84_CYCLE
#define ADC_SAMPLE_112_CYCLE
#define ADC_SAMPLE_144_CYCLE
#define ADC_SAMPLE_480_CYCLE


/***********************ADC REGISTER BIT DEFINATION**********************/

//ADC CONTROL REGISTER 1
#define ADC_CR1_OVRIE			26
#define ADC_CR1_AWDEN			23
#define ADC_CR1_JAWDEN			22
#define ADC_CR1_DISCNUM			13
#define ADC_CR1_JDISCEN			12
#define ADC_CR1_DISCEN			11
#define ADC_CR1_JAUTO			10
#define ADC_CR1_AWDSGL			9
#define ADC_CR1_SCAN			8
#define ADC_CR1_JEOCIE			7
#define ADC_CR1_AWDIE			6
#define ADC_CR1_EOCIE			5
#define ADC_CR1_AWDCH			0

//ADC CONTROL REGISTER 2
#define ADC_CR2_SWSTART			30
#define ADC_CR2_EXTEN			28
#define ADC_CR2_EXTSEL			24
#define ADC_CR2_JSWSTART		22
#define ADC_CR2_JEXTEN			20
#define ADC_CR2_JEXTSEL			16
#define ADC_CR2_ALIGN			11
#define ADC_CR2_EOCS			10
#define ADC_CR2_DDS				9
#define ADC_CR2_DMA				8
#define ADC_CR2_CONT			1
#define adc_cr2_ADON			0







#endif /* HEADERS_ADC_H_ */
