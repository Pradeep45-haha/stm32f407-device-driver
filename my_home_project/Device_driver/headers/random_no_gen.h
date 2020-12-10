/*
 * random_no_gen.h
 *
 *  Created on: 20-May-2020
 *      Author: emes
 */

#ifndef HEADERS_RANDOM_NO_GEN_H_
#define HEADERS_RANDOM_NO_GEN_H_

#include "stm32f4.h"

typedef struct
{
	uint8_t RNG_Interrupt_EnorDi;

}RNG_Config_t;

typedef struct
{
	RNG_Config_t RNG_Config;
	RNG_RegDef_t  *pRNG;
	uint32_t ran_num;
}RNG_Handle_t;


//RNG INTERRUPT ENABLE OR DISABLE POSSIBLE VALUES
#define RNG_INTERRUPT_EN	1
#define RNG_INTERRUPT_DI	0


//RNG PERIPHERAL BIT DEFINATION
#define RNG_CR_RNGEN		2
#define RNG_CR_IE			3

#define RNG_SR_DRDY			0
#define RNG_SR_CECS			1
#define RNG_SR_SECS			2
#define RNG_SR_CEIS			5
#define RNG_SR_SEIS			6



//PROTOTYPE API FOR RNG PERIPHERAL

//RNG PHERIPHERAL CLOCK EN OR DI API
void RNG_PCLK_ENorDI(uint8_t ENorDI);

//RNG PERIPHERAL EN OR DISABLE OR RESET
void RNG_ENorDI(RNG_Handle_t Random_no_gen, uint8_t ENorDI);
void RNG_INIT(RNG_Handle_t RNG_Config);
void RND_DEINIT(void);

//GNG PERIPHERAL GET RANDOM NUMBER
uint32_t GET_RNG_NO(RNG_Handle_t Random_no_gen);
uint32_t CHECK_RNG_NO(RNG_Handle_t Random_no_gen);

//RNG PERIPHERAL INTERRUPT
void RNG_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void RNG_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void RNG_IRQHandling(RNG_Handle_t Random_no_gen);

//RNG OTHER API
uint8_t RNG_GetFlagStatus(RNG_Handle_t Random_no_gen, uint32_t status_name);

#endif /* HEADERS_RANDOM_NO_GEN_H_ */
