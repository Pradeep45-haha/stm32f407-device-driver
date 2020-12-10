/*
 * stm32f4.h
 *
 *  Created on: 21-Oct-2019
 *      Author: emes
 */

#ifndef HEADERS_STM32F4_H_
#define HEADERS_STM32F4_H_

#include "stdint.h"
#include "stddef.h"

#define __vo volatile

//NVIC REGISTER ADDRESS
#define NVIC_ISER0                      ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1                      ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2                      ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3                      ((__vo uint32_t*)0xE000E10C)

#define NVIC_ICER0                      ((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1                      ((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2                      ((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3                      ((__vo uint32_t*)0XE000E18C)

#define NVIC_PR_BASEADDR                ((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPL                 4

//SYSTEM MEMORY AND RAM ROM BASE ADDRESSES
#define SRAM1_BASEADDR        0x20000000U
#define FLASH_BASEDDR         0x08000000U
#define SRAM2_BASEADDR        0x2001C000U
#define ROM_BASEADDR          0x1FFF0000U
#define SRAM                  SRAM1_BASEADDR


//BASE ADDRESSES OF VARIOUS PERIPHERAL BUS
#define PERIPHERAL_BASEADDR    0x40000000U
#define APB1_BASEADDR          PERIPHERAL_BASEADDR
#define APB2_BASEADDR          0x40010000U
#define AHB1_BASEADDR          0x40020000U
#define AHB2_BASEADDR          0x50000000U
#define AHB3_BASEADDR          0xA0000000U


//BASE ADDRESS OF PERIPHERAL WHICH ARE HANGING ON AHB1 BUS
#define GPIOA_BASEADDR        (0x40020000U)
#define GPIOB_BASEADDR        (0x40020400U)
#define GPIOC_BASEADDR        (0x40020800U)
#define GPIOD_BASEADDR        (0x40020C00U)
#define GPIOE_BASEADDR        (0x40021000U)
#define GPIOF_BASEADDR        (0x40021400U)
#define GPIOG_BASEADDR        (0x40021800U)
#define GPIOH_BASEADDR        (0x40021C00U)
#define GPIOI_BASEADDR        (0x40022000U)
#define RCC_BASEADDR          (0x40023800U)
#define DMA1_BASEADDR         (0x40026000U)
#define DMA2_BASEADDR         (0x40026400U)


//BASE ADDRESS OF PERIPHERAL WHICH ARE HANGING ON AHB2 BUS
#define RNG_BASEADDR		  (0x50060800)

//BASE ADDRESS OF PERIPHERAL WHICH ARE HANGING ON APB1 BUS
#define I2C1_BASEADDR         (0x40005400U)
#define I2C2_BASEADDR         (0x40005800U)
#define I2C3_BASEADDR         (0x40005C00U)
#define SPI2_BASEADDR         (0x40003800U)
#define SPI3_BASEADDR         (0x40003C00U)
#define USART2_BASEADDR       (0x40004400U)
#define USART3_BASEADDR       (0x40004800U)
#define UART4_BASEADDR        (0x40004C00U)
#define UART5_BASEADDR        (0x40005000U)
#define TIM6_BASEADDR         (0x40001000U)
#define TIM7_BASEADDR         (0x40001400U)


//BASE ADDRESS OF PERIPHERAL WHICH ARE HANGING ON APB2 BUS
#define SPI1_BASEADDR         (0x40013000U)
#define USART1_BASEADDR       (0x40011000U)
#define USART6_BASEADDR       (0x40011400U)
#define EXTI_BASEADDR         (0x40013C00U)
#define SYSCFG_BASEADDR       (0x40013800U)
#define ADC_BASEADDR		  (0x40012000U)


//ADC REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t SR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SMPR1;
	__vo uint32_t SMPR2;
	__vo uint32_t JOFR1;
	__vo uint32_t JOFR2;
	__vo uint32_t JOFR3;
	__vo uint32_t JOFR4;
	__vo uint32_t HTR;
	__vo uint32_t LTR;
	__vo uint32_t SQR1;
	__vo uint32_t SQR2;
	__vo uint32_t SQR3;
	__vo uint32_t JSQR;
	__vo uint32_t JDR1;
	__vo uint32_t JDR2;
	__vo uint32_t JDR3;
	__vo uint32_t JDR4;
	__vo uint32_t DR;

}ADC_RegDef_t;

//DMA REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t LISR;
	__vo uint32_t HISR;
	__vo uint32_t LIFCR;
	__vo uint32_t HIFCR;
	__vo uint32_t S0CR;
	__vo uint32_t S0NDTR;
	__vo uint32_t S0PAR;
	__vo uint32_t S0M0AR;
	__vo uint32_t S0M1AR;
	__vo uint32_t S0FCR;
	__vo uint32_t S1CR;
	__vo uint32_t S1NDTR;
	__vo uint32_t S1PAR;
	__vo uint32_t S1M0AR;
	__vo uint32_t S1M1AR;
	__vo uint32_t S1FCR;
	__vo uint32_t S2CR;
	__vo uint32_t S2NDTR;
	__vo uint32_t S2PAR;
	__vo uint32_t S2M0AR;
	__vo uint32_t S2M1AR;
	__vo uint32_t S2FCR;
	__vo uint32_t S3CR;
	__vo uint32_t S3NDTR;
	__vo uint32_t S3PAR;
	__vo uint32_t S3M0AR;
	__vo uint32_t S3M1AR;
	__vo uint32_t S3FCR;
	__vo uint32_t S4CR;
	__vo uint32_t S4NDTR;
	__vo uint32_t S4PAR;
	__vo uint32_t S4M0AR;
	__vo uint32_t S4M1AR;
	__vo uint32_t S4FCR;
	__vo uint32_t S5CR;
	__vo uint32_t S5NDTR;
	__vo uint32_t S5PAR;
	__vo uint32_t S5M0AR;
	__vo uint32_t S5M1AR;
	__vo uint32_t S5FCR;
	__vo uint32_t S6CR;
	__vo uint32_t S6NDTR;
	__vo uint32_t S6PAR;
	__vo uint32_t S6M0AR;
	__vo uint32_t S6M1AR;
	__vo uint32_t S6FCR;
	__vo uint32_t S7CR;
	__vo uint32_t S7NDTR;
	__vo uint32_t S7PAR;
	__vo uint32_t S7M0AR;
	__vo uint32_t S7M1AR;
	__vo uint32_t S7FCR;

}DMA_RegDef_t;

//GPIO REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];

}GPIO_RegDef_t;


//SPI REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

}SPI_RegDef_t;


//I2C REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
	__vo uint32_t FLTR;

}I2C_RegDef_t;


//USART REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t BRR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;
}USART_RegDef_t;


//RANDOM NUMBER GENERATOR REGISTER
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t SR;
	__vo uint32_t DR;
}RNG_RegDef_t;


//BASIC TIMER REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
		 uint32_t RESERVED;
	__vo uint32_t DIER;
	__vo uint32_t SR;
	__vo uint32_t EGR;
		 uint32_t RESERVED1;
		 uint32_t RESERVED2;
		 uint32_t RESERVED3;
	__vo uint32_t CNT;
	__vo uint32_t PSC;
	__vo uint32_t ARR;

}TIMER_B_RegDef_t;


//RCC REGISTER STRUCTURE
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	     uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	     uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	     uint32_t RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	     uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	     uint32_t RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	     uint32_t RESERVED5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	     uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;

}RCC_RegDef_t;


//EXTI PERIPHERAL REGISTOR  STRUCTURE
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;

}EXTI_RegDef_t;


//SYSCFG PERIPHERAL REGISTOR  STRUCTURE
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t CMPCR;

}SYSCFG_RegDef_t;


//ADC PERIPHERAL
#define ADC								((ADC_RegDef_t*)ADC_BASEADDR)
#define ADC1							((__vo uint32_t*)ADC_BASEADDR)
#define ADC2							((__vo uint32_t*)ADC_BASEADDR + 0x100)
#define ADC3							((__vo uint32_t*)ADC_BASEADDR + 0x200)

//CLOCK ENABLE MACRO FOR ADC
#define ADC1_PCLK_EN() 					(RCC->APB2ENR |= (1 << 8))
#define ADC2_PCLK_EN()					(RCC->APB2ENR |= (1 << 9))
#define ADC3_PCLK_EN()					(RCC->APB2ENR |= (1 << 10))

//CLOCK DISABLE MACRO FOR ADC
#define ADC1_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 8))
#define ADC2_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 9))
#define ADC3_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 10))

//ADC REGISTER RESET MACRO
#define ADC_REG_RESET()					do{(RCC->APB2RSTR |= (1 << 8)); (RCC->APB2RSTR &= ~(1 << 8));}while(0)

//DMA PERIPHERAL
#define DMA1							((DMA_RegDef_t*)DMA1_BASEADDR)
#define DMA2							((DMA_RegDef_t*)DMA2_BASEADDR)

//CLOCK ENABLE MACRO FOR DMA
#define DMA1_PCLK_EN()					(RCC->AHB1ENR |= (1 << 21))
#define DMA2_PCLK_EN()					(RCC->AHB1ENR |= (1 << 22))

//CLOCK DISABLE MACRO FOR DMA
#define DMA1_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 21))
#define DMA2_PCLK_DI()					(RCC->AHB1ENR &= ~(1 << 22))

//MACRO TO RESET DMA PERIPHERAL
#define DMA1_REG_RESET()				do{(RCC->AHB1RSTR |= (1 << 21)); (RCC->AHB1RSTR &= ~(1 << 21));}while(0)
#define DMA2_REG_RESET()				do{(RCC->AHB1RSTR |= (1 << 22)); (RCC->AHB1RSTR &= ~(1 << 22));}while(0)

//RCC
#define RCC								((RCC_RegDef_t*)RCC_BASEADDR)

//GPIO PERIPHERAL
#define GPIOA                            ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                            ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                            ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                            ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                            ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                            ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                            ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH                            ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI                            ((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define RCC                              ((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI                             ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG                           ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


//CLOCK ENABLE MACRO FOR GPIOx PERIPHERALS
#define GPIOA_PCLK_EN()             (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()             (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()             (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()             (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()             (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()             (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()             (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()             (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()             (RCC->AHB1ENR |= (1 << 8))


//CLOCK DISABLE MACRO FOR GPIOx PERIPHERALS
#define GPIOA_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 8))


//SYSGIF CLOCK ENABLE DISABLE MACRO
#define SYSCFG_PCLK_EN()             (RCC->APB2ENR |= (1 << 14))
#define SYSCFG_PCLK_DI()             (RCC->APB2ENR &= ~(1 << 14))


//MACROS TO RESET GPIO PERIPHERALS
#define GPIOA_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)
#define GPIOI_REG_RESET()            do{(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8));}while(0)


//SPI PERIPHERALS
#define SPI1                         ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2                         ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3                         ((SPI_RegDef_t*)SPI3_BASEADDR)


//CLOCK ENABLE MACROS FOR SPIX PERIPHERAL
#define SPI1_PCLK_EN()                 (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()                 (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()                 (RCC->APB1ENR |= (1 << 15))


//CLOCK ENABLE MACROS FOR SPIX PERIPHERAL
#define SPI1_PCLK_DI()                 (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 15))


//MACROS TO RESET SPI REGISTERS
#define SPI1_REG_RESET()               do{(RCC->APB2RSTR |= (1 << 12)); RCC->APB2RSTR &= ~(1 << 12);}while(0)
#define SPI2_REG_RESET()			   do{(RCC->APB1RSTR |= (1 << 14)); RCC->APB1RSTR &= ~(1 << 14);}while(0)
#define SPI3_REG_RESET()               do{(RCC->APB1RSTR |= (1 << 15)); RCC->APB1RSTR &= ~(1 << 15);}while(0)


//I2C PERIPHERALS
#define I2C1							((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2							((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3							((I2C_RegDef_t*)I2C3_BASEADDR)


//CLOCK ENABLE MACROS FOR I2C PERIPHERALS
#define I2C1_PCLK_EN()					(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()					(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()					(RCC->APB1ENR |= (1 << 23))


//CLOCK DISABLE MACROS FOR I2C PERIPHERALS
#define I2C1_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 23))


//MARCOS TO RESET I2C PERIPHERAL
#define I2C1_REG_RESET()				do{(RCC->APB1RSTR |= (1 << 21));RCC->APB1RSTR &= ~(1 << 21);}while(0)
#define I2C2_REG_RESET()				do{(RCC->APB1RSTR |= (1 << 22));RCC->APB1RSTR &= ~(1 << 22);}while(0)
#define I2C3_REG_RESET()				do{(RCC->APB1RSTR |= (1 << 23));RCC->APB1RSTR &= ~(1 << 23);}while(0)


//USART PERIPHERAL
#define USART1							((USART_RegDef_t*)USART1_BASEADDR)
#define USART2							((USART_RegDef_t*)USART2_BASEADDR)
#define USART3							((USART_RegDef_t*)USART3_BASEADDR)
#define UART4							((USART_RegDef_t*)UART4_BASEADDR)
#define UART5							((USART_RegDef_t*)UART5_BASEADDR)
#define USART6							((USART_RegDef_t*)USART6_BASEADDR)


//CLOCK ENABLE MACROS FOR USART
#define USART1_PCLK_EN()							(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()							(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()							(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()								(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()								(RCC->APB2ENR |= (1 << 20))
#define USART6_PCLK_EN()							(RCC->APB2ENR |= (1 << 5))


//CLOCK DISABLE MACROS FOR USART
#define USART1_PCLK_DI()							(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()							(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()							(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()								(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()								(RCC->APB2ENR &= ~(1 << 20))
#define USART6_PCLK_DI()							(RCC->APB2ENR &= ~(1 << 5))


//USART REGISTER RESET MACROS
#define USART1_REG_RESET()						do{(RCC->APB2RSTR |= (1 << 4));  RCC->APB2RSTR  &= ~(1 << 4);}while(0);
#define USART2_REG_RESET()						do{(RCC->APB1RSTR |= (1 << 17)); RCC->APB1RSTR &= ~(1 << 17);}while(0);
#define USART3_REG_RESET()						do{(RCC->APB1RSTR |= (1 << 18)); RCC->APB1RSTR &= ~(1 << 18);}while(0);
#define UART4_REG_RESET()						do{(RCC->APB1RSTR |= (1 << 19)); RCC->APB1RSTR &= ~(1 << 19);}while(0);
#define UART5_REG_RESET()						do{(RCC->APB1RSTR |= (1 << 20)); RCC->APB1RSTR &= ~(1 << 20);}while(0);
#define USART6_REG_RESET()						do{(RCC->APB2RSTR |= (1 << 5));  RCC->APB2RSTR  &= ~(1 << 5);}while(0);

//BASIC TIMER
#define TIM6									((TIMER_B_RegDef_t*)TIM6_BASEADDR)
#define TIM7									((TIMER_B_RegDef_t*)TIM7_BASEADDR)

//CLOCK ENABLE MACROS FOR BASIC TIMER
#define TIM6_PCLK_EN()							 (RCC->APB1ENR |= (1 << 4))
#define TIM7_PCLK_EN()							 (RCC->APB1ENR |= (1 << 5))

//CLOCK DISABLE MACROS FOR BASIC TIMER
#define TIM6_PCLK_DI()							 (RCC->APB1ENR &= ~(1 << 4))
#define TIM7_PCLK_DI()							 (RCC->APB1ENR &= ~(1 << 5))

//BASIC TIMER REGISTER RESET MACRO
#define TIM6_REG_RESET()				do{(RCC->APB1RSTR |= (1 << 4)); RCC->APB1RSTR &= ~(1 << 4);}while(0);
#define TIM7_REG_RESET()				do{(RCC->APB1RSTR |= (1 << 5)); RCC->APB1RSTR &= ~(1 << 5);}while(0);

//RNG PERIPHERAL
#define RNG										((RNG_RegDef_t*)RNG_BASEADDR)

//CLOCK ENABLE MACROS FOR RNG PERIPHERAL
#define RNG_PCLK_EN()							(RCC->AHB2ENR |= (1 << 6))


//CLOCK DISABLE MACROS FOR RNG PERIPHERAL
#define RNG_PCLK_DI()							(RCC->AHB2ENR &= ~(1 << 6))


//RNG PERIPHERAL REG RESET MACROS
#define RNG_REG_RESET()							do{(RCC->AHB2RSTR |= (1 << 6));  RCC->AHB2RSTR  &= ~(1 << 6);}while(0);


//IRQ NUMBERS
#define I2C1_IRQ_EV		31
#define I2C1_IRQ_ER		32

#define RNG_IRQ			80

#define TIM6_DAC		54


//MIXED MACROS
#define ENABLE                       1
#define DISABLE                      0
#define SET                          ENABLE
#define RESET                        DISABLE
#define READ						 DISABLE
#define WRITE						 ENABLE
#define GPIO_PIN_SET                 SET
#define GPIO_PIN_RESET               RESET
#define FLAG_RESET                   RESET
#define FLAG_SET                     SET


#endif /* HEADERS_STM32F4_H_ */
