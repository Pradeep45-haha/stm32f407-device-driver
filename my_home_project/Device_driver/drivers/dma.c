/*
 * dma.c
 *
 *  Created on: 05-Dec-2020
 *      Author: emes
 */
#include "dma.h"

/*******************APIs SUPPORTED BY THIS DRIVER*********************/

void DMA_Enable_PeripheralClk(DMA_RegDef_t *pDMAx)
{
	if(pDMAx == DMA1)
	{
		DMA1_PCLK_EN();
	}else if(pDMAx == DMA2)
	{
		DMA2_PCLK_EN();
	}else
	{
		return;
	}

}


void DMA_Disbale_PeripheralClk(DMA_RegDef_t *pDMAx)
{
	if(pDMAx == DMA1)
	{
		DMA1_PCLK_DI();
	}else if(pDMAx == DMA2)
	{
		DMA2_PCLK_DI();
	}else
	{
		return;
	}

}


void DMA_Register_Reset(DMA_RegDef_t *pDMAx)
{
	if(pDMAx == DMA1)
	{
		DMA1_REG_RESET();
	}else if(pDMAx == DMA2)
	{
		DMA2_REG_RESET();
	}else
	{
		return;
	}

}


void DMA_Config_ForTransfer(DMA_Handle_t DMA_Stream_Handle)
{

	uint32_t tempReg1, tempReg2;
	tempReg1 = tempReg2 = 0;

	//PROGRAM DMA CHANNEL VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_Channel << DMA_SCR_CHSEL;

	if(DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_DirectMode_DIS == DMA_DIRECT_MODE_DI)
	{
	//PROGRAM THE CONFIGURED CIRCULAR MODE VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_CircularMode << DMA_SCR_CIRC;

	//PROGRAM DOUBLE BUFFER MODE VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_DoubleBufferMode << DMA_SCR_DBM;

	//PROGRAM MEMORY BURST VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_MemoryBrustConfig << DMA_SCR_MBURST;

	//PROGRAM THE VALUE OF PERIPHERAL BURST
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralBrustConfig << DMA_SCR_PBURST;

	//PROGRAM MEMORY DATA SIZE VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_MemoryDataSize << DMA_SCR_MSIZE;

	//PROGRAM THE CURRENT TARGET VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_currentTarget << DMA_SCR_CT;
	}

	//PROGRAM THE CONFIGURE DATA DIRECTION VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_DataDirection  <<DMA_SCR_DIR;

	//PROGRAM THE MEMORY POINTER INC VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_MemoryPointerInc << DMA_SCR_MINC;

	//PROGRAM THE VLAUE OF PERIPHERAL DATA SIZE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralDataSize << DMA_SCR_PSIZE;

	//PROGRAM PERIPHERAL FLOW CONTROLLER VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController << DMA_SCR_PFCTRL;

	//PROGRAM PERIPHERAL INCREMENT OFFSET SIZE VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralIncOffsetSize << DMA_SCR_PINCOS;

	//PROGRAM THE PERIPHERAL POINTER INC VALUE
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralPointerInc << DMA_SCR_PINC;

	//PROGRAM THE STREAM PRIORITY LEVEL
	tempReg1 |= DMA_Stream_Handle.DMA_Stream_Config.DMA_StreamPriority << DMA_SCR_PL;


	/*******************PROGRAMMING FOR FIFO CONTROL REGISTER****************************/

	if(DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_DirectMode_DIS == DMA_DIRECT_MODE_DI)
	{
	//PROGRAM THE FIFO THRESHOLD VALUE
	tempReg2 |= DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Threshold << DMA_SFCR_FTH;
	}else
	{
	//PROGRAM THE CONFGURED DIRECT MODE VALUE
	tempReg2 |= DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_DirectMode_DIS << DMA_SFCR_DMDIS;
	}



	switch(DMA_Stream_Handle.DMA_Stream)
	{

	case DMA_STREAM_0:

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S0CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S0CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DMA STREAM_0 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S0CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S0FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S0PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S0M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S0NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_1:

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S1CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S1CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_0 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S1CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S1FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S1PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S1M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S1NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_2:

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S2CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S2CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_2 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S2CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S2FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S2PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S2M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S2NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_3:

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S3CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S3CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_3 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S3CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S3FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S3PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S3M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S3NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_4:

		/*****************PROGRAMMING FOR DMA_STREAM_4****************/

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S4CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S4CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_4 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S4CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S4FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S4PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S4M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S4NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_5:

		/*****************PROGRAMMING FOR DMA_STREAM_5****************/

		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S5CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S5CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_5 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S5CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S5FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S5PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S5M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S5NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_6:

		/*****************PROGRAMMING FOR DMA_STREAM_6****************/
		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S6CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S6CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_6 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S6CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S6FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S6PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S6M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S6NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;


	case DMA_STREAM_7:

		/*****************PROGRAMMING FOR DMA_STREAM_7****************/
		//FIRST DISABLE THE DMA STREAM
		DMA_Stream_Handle.pDMAx->S7CR &= ~(1 << DMA_SCR_EN);

		//WAIT UNTIL DAM STREAM ENEABLE REG VALUE READ AS RESET
		while(!(DMA_Stream_Handle.pDMAx->S7CR & (1 << DMA_SCR_EN)));

		//PROGRAM THE DAM STREAM_7 CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S7CR = tempReg1;

		//PROGRAM THE DMA FIFO CONTROL REGISTER
		DMA_Stream_Handle.pDMAx->S7FCR |= tempReg2;


		/****************PROGRAMMING FOR NO. OF DATA TO TRANSFER AND ADDRESS OF MEMORY AND PERIPHERAL*************/

		DMA_Stream_Handle.pDMAx->S7PAR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_PeripheralAddress;

		DMA_Stream_Handle.pDMAx->S7M0AR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_Memory_0_Address;

		if(DMA_Stream_Handle.DMA_Stream_Config.DMA_PeripheralFlowController == DMA_FLOW_CONTROLLER_DMA)
		{
			DMA_Stream_Handle.pDMAx->S7NDTR = DMA_Stream_Handle.DMA_Stream_DataNum_Config_t.DMA_NumberOfData;
		}

		break;

	default:
		;
	}
}


void DMA_Get_FIFOStatus(DMA_Handle_t DMA_Stream_Handle)
{

	switch(DMA_Stream_Handle.DMA_Stream)
	{
	case DMA_STREAM_0:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S0FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_1:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S1FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_2:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S2FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_3:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S3FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_4:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S4FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_5:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S5FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_6:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S6FCR << DMA_SFCR_FS;

	break;

	case DMA_STREAM_7:
	DMA_Stream_Handle.DMA_FIFO_Config_t.DMA_FIFO_Status	= DMA_Stream_Handle.pDMAx->S7FCR << DMA_SFCR_FS;

	break;

	default:
		;
	}
}


void DMA_Config_Interrupt(DMA_Handle_t DMA_Stream_Handle)
{
	uint32_t tempreg = 0;

	tempreg |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_DirectModeError_INT_EN;
	tempreg |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_HalfTransfer_INT_EN;
	tempreg |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_TransferComplete_INT_EN;
	tempreg |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_TransferError_INT_EN;

	switch(DMA_Stream_Handle.DMA_Stream)
	{
	case DMA_STREAM_0:

		DMA_Stream_Handle.pDMAx->S0CR = tempreg;
		DMA_Stream_Handle.pDMAx->S0FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;

		break;

	case DMA_STREAM_1:

		DMA_Stream_Handle.pDMAx->S1CR = tempreg;
		DMA_Stream_Handle.pDMAx->S1FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_2:

		DMA_Stream_Handle.pDMAx->S2CR = tempreg;
		DMA_Stream_Handle.pDMAx->S2FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_3:

		DMA_Stream_Handle.pDMAx->S3CR = tempreg;
		DMA_Stream_Handle.pDMAx->S3FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_4:

		DMA_Stream_Handle.pDMAx->S4CR = tempreg;
		DMA_Stream_Handle.pDMAx->S4FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_5:

		DMA_Stream_Handle.pDMAx->S5CR = tempreg;
		DMA_Stream_Handle.pDMAx->S5FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_6:

		DMA_Stream_Handle.pDMAx->S6CR = tempreg;
		DMA_Stream_Handle.pDMAx->S6FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;

	case DMA_STREAM_7:

		DMA_Stream_Handle.pDMAx->S7CR = tempreg;
		DMA_Stream_Handle.pDMAx->S7FCR |= DMA_Stream_Handle.DMA_StreamInterrupt_Config_t.DMA_FIFOError_INT_EN;
		break;
	default:
		;
	}

}


void DMA_Enable_stream(DMA_Handle_t DMA_Streamx)
{
	switch(DMA_Streamx.DMA_Stream)
	{
	case DMA_STREAM_0:
		DMA_Streamx.pDMAx->S0CR |= ENABLE;

		break;

	case DMA_STREAM_1:
		DMA_Streamx.pDMAx->S1CR |= ENABLE;

		break;

	case DMA_STREAM_2:
		DMA_Streamx.pDMAx->S2CR |= ENABLE;

		break;

	case DMA_STREAM_3:
		DMA_Streamx.pDMAx->S3CR |= ENABLE;

		break;

	case DMA_STREAM_4:
		DMA_Streamx.pDMAx->S4CR |= ENABLE;

		break;

	case DMA_STREAM_5:
		DMA_Streamx.pDMAx->S5CR |= ENABLE;

		break;

	case DMA_STREAM_6:
		DMA_Streamx.pDMAx->S6CR |= ENABLE;

		break;

	case DMA_STREAM_7:
		DMA_Streamx.pDMAx->S7CR |= ENABLE;

		break;

	default:
		;
	}

}



