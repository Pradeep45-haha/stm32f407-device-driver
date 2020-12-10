/*
 * rcc.h
 *
 *  Created on: 12-May-2020
 *      Author: emes
 */

#ifndef HEADERS_RCC_H_
#define HEADERS_RCC_H_

#include "stm32f4.h"

//RCC REGISTER BIT DEFINATION
#define RCC_CR_HSION		0
#define RCC_CR_HSIRDY		1
#define RCC_CR_HSITRIM		3
#define RCC_CR_HSICAL		8
#define RCC_CR_HSEON		16
#define RCC_CR_HSERDY		17
#define RCC_CR_HSEBYP		18
#define RCC_CR_CSSON		19
#define RCC_CR_PLLON		24
#define RCC_CR_PLLRDY		25
#define RCC_CR_PLLI2SON		26
#define RCC_CR_PLLI2SRDY	27


#define RCC_PLL_CFGR_PLLM0		0
#define RCC_PLL_CFGR_PLLM1		1
#define RCC_PLL_CFGR_PLLM2		2
#define RCC_PLL_CFGR_PLLM3		3
#define RCC_PLL_CFGR_PLLM4		4
#define RCC_PLL_CFGR_PLLM5		5
#define RCC_PLL_CFGR_PLLN		6
#define RCC_PLL_CFGR_PLLP0		16
#define RCC_PLL_CFGR_PLLP1		17
#define RCC_PLL_CFGR_PLLSRC   	22
#define RCC_PLL_CFGR_PLLQ0		24
#define RCC_PLL_CFGR_PLLQ1		25
#define RCC_PLL_CFGR_PLLQ2		26
#define RCC_PLL_CFGR_PLLQ3		27


#define RCC_CFGR_SW0		0
#define RCC_CFGR_SW1		1
#define RCC_CFGR_SWS0		2
#define RCC_CFGR_SWS1		3
#define RCC_CFGR_HPRE		4
#define RCC_CFGR_PPRE1		10
#define RCC_CFGR_PPRE2		13
#define RCC_CFGR_RTCPRE		16
#define RCC_CFGR_MCO1		21
#define RCC_CFGR_I2SSCR		23
#define RCC_CFGR_MCO1PRE	24
#define RCC_CFGR_MCO2PRE	27
#define RCC_CFGR_MCO2		30


//APIS TO CONFIGURE DIFFERENT CLOCK
void RCC_PLL_Config(void);




//API TO GET THE VAUE OF CLOCK
uint32_t RCC_PCLK1_VALUE(void);
uint32_t RCC_PCLK2_VALUE(void);
uint32_t RCC_PLL(void);



#endif /* HEADERS_RCC_H_ */
