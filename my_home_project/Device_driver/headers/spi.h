/*
 * spi.h
 *
 *  Created on: 12-Nov-2019
 *      Author: emes
 */

#ifndef HEADERS_SPI_H_
#define HEADERS_SPI_H_

#include "stdint.h"
#include "stddef.h"

#define __vo volatile
#include "stm32f4.h"

//SPI PIN CONFIGURATOIN
typedef struct
{
	uint8_t SPI_Device_mode;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_Clock_speed;
	uint8_t SPI_Bus_config;
	uint8_t SPI_Simplex;
	uint8_t SPI_Data_frame_size;
	uint8_t SPI_Software_slave_mngmt;

}SPI_PinConfig_t;


//SPI HANDLE STRUCTURE
typedef struct
{
	SPI_RegDef_t          *pSPIx;
	SPI_PinConfig_t        SPI_PinConfig;
	uint32_t              *pTxBuffer;
	uint32_t              *pRxBuffer;
	uint32_t               TxLen;
	uint32_t               RxLen;
	uint8_t                TxState;
	uint8_t                RxState;
}SPI_Handle_t;


//SPI DEVICE POSSIBLE MODE
#define SPI_DEVICE_SLAVE_MODE			0
#define SPI_DEVICE_MASTER_MODE			1


//SPI CLOCK POLARITY POSSIBLE VALUE
#define SPI_CPOL_LOW				0
#define SPI_CPOL_HIGH				1


//SPI CLOCK PHASE POSSIBLE VALUE
#define SPI_CPHA_LOW				0
#define SPI_CPHA_HIGH				1


//SPI CLOCK SPEED POSSIBLE VALUE
#define SPI_CLOCK_Speed_DIV2                  0
#define SPI_CLOCK_Speed_DIV4                  1
#define SPI_CLOCK_Speed_DIV8                  2
#define SPI_CLOCK_Speed_DIV16                 3
#define SPI_CLOCK_Speed_DIV32                 4
#define SPI_CLOCK_Speed_DIV64                 5
#define SPI_CLOCK_Speed_DIV128                6
#define SPI_CLOCK_Speed_DIV256                7


//SPI BUS POSSIBLE VALUE
#define SPI_BUS_2_UNI_DIR				0        //FULL DUPLEX TRANSMISSION
#define SPI_BUS_1_BI_DIR     			1		 //HALF DUPLEX TRANSMISSION


//SPI SIMPLEX POSSIBLE VALUE
#define SPI_Half_Duplex_Recive_only		0
#define SPI_Half_Duplex_Transmit_only	1


//SPI DATA FRAME SIZE POSSIBLE VALUE
#define SPI_DATA_8_BITS				0
#define SPI_DATA_16_BITS			1


//SPI SOFTWARE SLAVE MANAGEMENT
#define SPI_SOFTWARE_DISABLE			0
#define SPI_SOFTWARE_ENABLE				1

//OTHER MACROS USED IN SPI_HANDLE_T DATA STRUCTURE
//STATE OF SPI
#define SPI_Ready                        0
#define SPI_Busy_In_Rx                   1
#define SPI_Busy_In_Tx                   2

//POSSIBLE SPI APPLICATION EVENT
#define SPI_EVENT_TX_CMPLT               0
#define SPI_EVENT_RX_CMPLT               1
#define SPI_EVENT_OVR_ERROR              2


//SPI FLAG
#define SPI_SR_RXNE               (1)
#define SPI_SR_TXE                (1 << 1)
#define SPI_SR_CHSIDE             (1 << 2)
#define SPI_SR_UDR				  (1 << 3)
#define SPI_SR_CRCERR			  (1 << 4)
#define SPI_SR_MODF				  (1 << 5)
#define SPI_SR_OVR				  (1 << 6)
#define SPI_SR_BSY				  (1 << 7)
#define SPI_SR_FRE				  (1 << 8)


//SPI PHERIPHERAL CLOCK CONTROLS APIS
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Peripheral_EnorDi(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


//SPI INIT AND DEINIT APIS
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


//SPI DATA SEND AND RECIVE APIS
void SPI_Send_Data(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_Recive_Data(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


//SPI SEND AND RECIVE DATA IN INTERRUPT MODE APIS
uint8_t SPI_INTERRUPT_Send_Data(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_INTERRUPT_Recive_Data(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);


//SPI IRQ CONFIGURATION AND ISR HANDLING APIS
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);


//SOME OTHER API
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSMConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
void SPI_Clear_OVR_Flag(SPI_RegDef_t *pSPIx);
void SPI_Close_Trans(SPI_Handle_t *pSPIHandle);
void SPI_Close_Rep(SPI_Handle_t *pSPIHandle);
void SPI_AppilicationEventCallBack(SPI_Handle_t *pSPIHandle , uint8_t AppEV);






#endif /* HEADERS_SPI_H_ */
