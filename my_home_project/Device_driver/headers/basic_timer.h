/*
 * basic_timer.h
 *
 *  Created on: 25-May-2020
 *      Author: emes
 */

#ifndef HEADERS_BASIC_TIMER_H_
#define HEADERS_BASIC_TIMER_H_

#include "stm32f4.h"

typedef struct
{
	uint16_t Basic_Timer_Prescler;
	uint16_t Basic_Timer_Auto_Reload_value;
	uint8_t	 Auto_Relod_Preload;
	uint8_t  One_Pulse_Mode;
	uint8_t  Update_Disable;
	uint8_t  Update_Request_Source;
	uint8_t  Master_Mode_Selection;
	uint8_t  Update_DMA_Request;
	uint8_t	 Update_Interrupt;
	uint8_t	 Event_Generation;
}BasicTim_Config_t;

typedef	struct
{
	BasicTim_Config_t Basic_timer_config;
	TIMER_B_RegDef_t  *pTIMx;
	uint16_t 		  Basic_Timer_counter;
	uint16_t 		  Auto_Reload_value;
	uint16_t 		  Prescaler_Value;
	uint16_t 		  Time_Passed;
}BasicTim_Handle_t;


//AUTO RELOAD PRELOAD
#define AUTO_RELOAD_PRELOAD_ENABLE		1		//TIMER ARR REGISTER IS BUFFERED
#define AUTO_RELOAD_PRELOAD_DISABLE		0		//TIMER ARR REGISTER IN NOT BUFFERED

//ONE PULSE MODE
#define ONE_PULSE_MODE_ENABLE			1		//COUNTER STOP COUNTING AT NEXT UPDATE EVENT
#define ONE_PULSE_MODE_DISABLE			0		//COUNTER IS NOT STOPPED AT UPDATE EVENT

//UPDATE DISABLE
#define UPDATE_DISABLE		1		//UPDATE EVENT IS NOT GENERATED
#define UPDATE_ENABLE		0		//THE UPDATE EVENT IS GENERATED

//UPDATE REQUEST SOURCE
#define UPDATE_REQUEST_SOURCE_COUNTER_UG_SMC	0
#define UPDATE_REQUEST_SOURCE_COUNTER			1

//MASTER MODE SELECTION
#define MASTER_MODE_RESET		0
#define MASTER_MODE_ENABLE		1
#define MASTER_MODE_UPDATE		2

//UPDATE DMA REQUEST
#define	UPDATE_REQUEST_DMA_ENABLE	1
#define UPDATE_REQUEST_DMA_DISABLE	0

//UPDTAE INTERRUPT
#define	UPDATE_INTERRUPT_ENABLE		1
#define UPDATE_INTERRUPT_DISABLE	0

//EVENT GENERATION
#define	EVENT_GENERATION	1

//TIMER REGISTER BIT DEFINATION

#define BASIC_TIM_CR1_CEN		0
#define BASIC_TIM_CR1_UDIS		1
#define BASIC_TIM_CR1_URS		2
#define BASIC_TIM_CR1_OPM		3
#define BASIC_TIM_CR1_ARPE		7

#define BASIC_TIM_CR2_MMS		4

#define BASIC_TIM_DIER_UIE		0
#define BASIC_TIM_DIER_UDE		8

#define BASIC_TIM_SR_UIF		0

#define BASIC_TIM_EGR_UG		0



//API SUPPORTED BY THIS DRIVER
void BASIC_TIMER_Init(BasicTim_Handle_t BASIC_TIMER_handle);
void BASIC_TIMER_DeInit(BasicTim_Handle_t *pBASIC_TIMERx);
void BASIC_TIMER_PeriClockControl(BasicTim_Handle_t *pBASIC_TIMERx, uint8_t EnorDi);

void BASIC_TIMER_GET_TIME(BasicTim_Handle_t BASIC_TIMER_handle);


//BASIC TIMER INTRREPUT
void BASIC_TIMER_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void BASIC_TIMER_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void BASIC_TIMER_IRQHandling(uint8_t PinNumber);

#endif /* HEADERS_BASIC_TIMER_H_ */
