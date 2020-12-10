/*
 * dma.h
 *
 *  Created on: 05-Dec-2020
 *      Author: emes
 */

#ifndef HEADERS_DMA_H_
#define HEADERS_DMA_H_

#include "stm32f4.h"
typedef struct
{
	uint8_t DMA_Channel;
	uint8_t DMA_DataDirection;
	uint8_t DMA_PeripheralFlowController;
	uint8_t DMA_PeripheralDataSize;
	uint8_t DMA_MemoryDataSize;
	uint8_t DMA_PeripheralPointerInc;
	uint8_t DMA_MemoryPointerInc;
	uint8_t DMA_PeripheralBrustConfig;
	uint8_t DMA_MemoryBrustConfig;
	uint8_t DMA_StreamPriority;
	uint8_t DMA_CircularMode;
	uint8_t DMA_DoubleBufferMode;
	uint8_t DMA_PeripheralIncOffsetSize;
	uint8_t DMA_currentTarget;

}DMA_Stream_Config_t;

typedef struct
{
	uint16_t DMA_NumberOfData;
	uint32_t* DMA_PeripheralAddress;
	uint32_t* DMA_Memory_0_Address;
	uint32_t* DMA_Memory_1_Address;
}DMA_Stream_DataNum_Config_t;

typedef struct
{
	uint8_t DMA_FIFO_Threshold;
	uint8_t DMA_FIFO_Status;
	uint8_t DMA_FIFO_DirectMode_DIS;
}DMA_FIFO_Config_t;

typedef struct
{
	uint8_t DMA_TransferComplete_INT_EN;
	uint8_t DMA_HalfTransfer_INT_EN;
	uint8_t DMA_TransferError_INT_EN;
	uint8_t DMA_DirectModeError_INT_EN;
	uint8_t DMA_FIFOError_INT_EN;
}DMA_Stream_IT_Config_t;

typedef struct
{
	DMA_RegDef_t 					*pDMAx;
	DMA_Stream_Config_t 			DMA_Stream_Config;
	DMA_Stream_IT_Config_t			DMA_StreamInterrupt_Config_t;
	DMA_Stream_DataNum_Config_t		DMA_Stream_DataNum_Config_t;
	DMA_FIFO_Config_t				DMA_FIFO_Config_t;
	uint8_t 						DMA_Stream;
}DMA_Handle_t;

/************************DMA HANDLE CONFIG POSSIBLE VALUE***********************/

//DMA STREAM POSSIBLE VALUE
#define DMA_STREAM_0		0
#define DMA_STREAM_1		1
#define DMA_STREAM_2		2
#define DMA_STREAM_3		3
#define DMA_STREAM_4		4
#define DMA_STREAM_5		5
#define DMA_STREAM_6		6
#define DMA_STREAM_7		7

//DMA CHANNEL POSSIBLE VALUES
#define DMA_CHANNEL_0			0
#define DMA_CHANNEL_1			1
#define DMA_CHANNEL_2			2
#define DMA_CHANNEL_3			3
#define DMA_CHANNEL_4			4
#define DMA_CHANNEL_5			5
#define DMA_CHANNEL_6			6
#define DMA_CHANNEL_7			7

//DMA DATA DIRECTION POSSIBLE VALUE
#define DMA_PERIPHERAL_TO_MEMORY		0
#define DMA_MEMORY_TO_PERIPHERAL		1
#define DMA_MEMORY_TO_MEMORY			2

//DMA PERIPHERAL FLOW CONTROLLER POSSIBLE VALUE
#define DMA_FLOW_CONTROLLER_DMA			0
#define DMA_FLOW_CONTROLLER_PERIPHERAL	1

//DMA PERIPHERAL DATA SIZE POSSIBLE VALUE
#define DMA_PERIPHERAL_BYTE				0
#define DMA_PERIPHERAL_HALF_WORD		1
#define DMA_PERIPHERAL_WORD				2

//DMA MEMORY DATA SIZE POSSIBLE VALUE
#define DMA_MEMORY_BYTE					0
#define DMA_MEMORY_HALF_WORD			1
#define DMA_MEMORY_WORD					2

//DMA POINTER INCREMENT POSSIBLE VALUE
#define DMA_PERIPHERAL_POINTER_INC_EN	1
#define DMA_PERIPHERAL_POINTER_INC_DI	0

#define DMA_MEMORY_POINTER_INC_EN		1
#define DMA_MEMORY_POINTER_INC_DI		0

//DMA BURST CONFIG
#define DMA_PERIPHERAL_BURST_SINGLE_TRANSFER	0
#define DMA_PERIPHERAL_BURST_INC_4				1
#define DMA_PERIPHERAL_BURST_INC_8				2
#define DMA_PERIPHERAL_BURST_INC_16				3

#define DMA_MEMORY_BURST_SINGLE_TRANSFER		0
#define DMA_MEMORY_BURST_INC_4					1
#define DMA_MEMORY_BURST_INC_8					2
#define DMA_MEMORY_BURST_INC_16					3

//DMA STREAM PRIORITY POSSIBLE VALUE
#define DMA_STREAM_PRI_VERY_HIGH		3
#define DMA_STREAM_PRI_HIGH				2
#define DMA_STREAM_PRI_MEDIUM			1
#define DMA_STREAM_PRI_LOW				0

//DMA CIRCULAR MODE POSSIBLE VALUE
#define DMA_CIRCULAR_MODE_DI			0
#define DMA_CIRCULAR_MODE_EN			1

//DMA DOUBLE BUFFER MODE  POSSIBLE VALUE
#define DMA_DOUBLE_BUFFER_MODE_DI		0
#define DMA_DOUBLE_BUFFER_MODE_EN		1

//DMA PERIPHERAL INCREMENT OFFSET SIZE POSSIBLE VALUE
#define DMA_PERIPHERAL_OFFSETLINKEDTO_PSIZE		0
#define DMA_PERIPHERAL_OFFSET_FIXED_TO_32BIT	1

//DMA CURRENT TARGET POSSIBLE VALUE
#define	DMA_CURRENT_TARGET_MEMORY_0		0
#define DMA_CURRENT_TARGET_MEMORY_1		1

//DMA FIFO THRESHOLD POSSIBLE VALUE
#define DMA_FIFO_THRESHOLD_1BY4			0
#define DMA_FIFO_THRESHOLD_1BY2			1
#define DMA_FIFO_THRESHOLD_2BY3			2
#define DMA_FIFO_THRESHOLD_FULL			3

//DMA DIRECT MODE POSSIBLE VALUE
#define DMA_DIRECT_MODE_DI			1
#define DMA_DIRECT_MODE_EN			0

//DMA INTERRUPT POSSIBLE MACROS
#define DMA_TRANSFER_COMPLET_INTERRUPT_EN		1
#define DMA_HALF_TRANSFER_INTERRUPT_EN			1
#define DMA_TRANSFER_INTERRUPT_EN				1
#define DMA_DIRECT_MODE_ERROR_INTERRUPT_EN		1
#define DMA_FIFO_ERROR_INTERRUPT_EN				1

#define DMA_TRANSFER_COMPLET_INTERRUPT_DI		0
#define DMA_HALF_TRANSFER_INTERRUPT_DI			0
#define DMA_TRANSFER_INTERRUPT_DI				0
#define DMA_DIRECT_MODE_ERROR_INTERRUPT_DI		0
#define DMA_FIFO_ERROR_INTERRUPT_DI				0

/*****************************DMA REGISTER BIT FEILD**************************/

//DMA SCR REGISTER BIT FEILD VALUE
#define	DMA_SCR_EN			0
#define DMA_SCR_DMEIE		1
#define DMA_SCR_TEIE		2
#define DMA_SCR_HTIE		3
#define DMA_SCR_TCIE		4
#define DMA_SCR_PFCTRL		5
#define DMA_SCR_DIR			6
#define DMA_SCR_CIRC		8
#define DMA_SCR_PINC		9
#define DMA_SCR_MINC		10
#define DMA_SCR_PSIZE		11
#define DMA_SCR_MSIZE		13
#define DMA_SCR_PINCOS		15
#define DMA_SCR_PL			16
#define DMA_SCR_DBM			18
#define DMA_SCR_CT			19
#define DMA_SCR_PBURST		21
#define DMA_SCR_MBURST		23
#define DMA_SCR_CHSEL		25


//DMA SFCR REGISTER BIT FIELD VALUE
#define DMA_SFCR_FTH		0
#define DMA_SFCR_DMDIS		2
#define DMA_SFCR_FS			3
#define DMA_SFCR_FEIE		7


/**********************APIs SUPPORTED BY THIS DRIVER******************/

void DMA_Enable_PeripheralClk(DMA_RegDef_t *pDMAx);
void DMA_Disbale_PeripheralClk(DMA_RegDef_t *pDMAx);
void DMA_Register_Reset(DMA_RegDef_t *pDAMx);
void DMA_Config_Interrupt(DMA_RegDef_t *pDMAx, DMA_Stream_IT_Config_t DMA_StreamIT);

void DMA_Config_ForTransfer(DMA_Handle_t DMA_Stream_Handle);
void DMA_Get_FIFOStatus(DMA_Stream_Config_t DMA_Streamx, DMA_FIFO_Config_t DMA_FIFO);
void DMA_Enable_stream(DMA_Handle_t DMA_Streamx);



/***************************************************END---------END---------END*****************************************************/

#endif /* HEADERS_DMA_H_ */
