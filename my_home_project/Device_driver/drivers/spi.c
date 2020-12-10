/*
 * spi.c
 *
 *  Created on: 12-Nov-2019
 *      Author: emes
 */

#include "spi.h"
#include "stdint.h"
#include "stddef.h"


//SPI APIS IMPLIMENTATION

//HELPER FUNCTIONS
void SPI_TXNE_Handler(SPI_Handle_t pSPIHandle)
{

				if(pSPIHandle.pSPIx->CR1 & (1 << 11))
				{
					//DATA IS 16 BIT FORMAT
					//LOAD THE DATA IN DR
					pSPIHandle.pSPIx->DR = *(uint16_t*)pSPIHandle.pTxBuffer;
					pSPIHandle.TxLen--;
					pSPIHandle.TxLen--;
					(uint16_t*)pSPIHandle.pTxBuffer++;
				}else
				{
					//DATA IS 8 BIT FORMAT
					//LOAD THE DATA IN DR
					pSPIHandle.pSPIx->DR = *(uint8_t*)pSPIHandle.pTxBuffer;
					pSPIHandle.TxLen--;
					(uint8_t*)pSPIHandle.pTxBuffer++;
				}
				if(pSPIHandle.TxLen == 0)
				{
					SPI_Close_Trans(&pSPIHandle);
					SPI_AppilicationEventCallBack(&pSPIHandle,SPI_EVENT_TX_CMPLT);
				}
}


void SPI_RXNE_Handler(SPI_Handle_t pSPIHandle)
{

				if(pSPIHandle.pSPIx->CR1 & (1 << 11))
				{
					//DATA IS 16 FORMAT
					//LOAD THE DATA FROM DR TO RXNE BUFFER
					*((uint16_t*)pSPIHandle.pRxBuffer) = pSPIHandle.pSPIx->DR;
					pSPIHandle.RxLen--;
					pSPIHandle.RxLen--;
					(uint16_t*)pSPIHandle.pRxBuffer++;
				}else
				{
					//DATA IS 8 FORMAT
					//LOAD THE DATA FROM DR TO RXNE BUFFER
					*((uint8_t*)pSPIHandle.pRxBuffer) = pSPIHandle.pSPIx->DR;
					pSPIHandle.RxLen--;
					(uint8_t*)pSPIHandle.pRxBuffer++;
				}
				if(pSPIHandle.RxLen == 0)
				{
					SPI_Close_Rep(&pSPIHandle);
					SPI_AppilicationEventCallBack(&pSPIHandle,SPI_EVENT_RX_CMPLT);
				}
}


void SPI_OVR_Handler(SPI_Handle_t pSPIHandle)
{
	uint8_t temp;
	if(pSPIHandle.TxState != SPI_Busy_In_Tx)
	{
		temp = pSPIHandle.pSPIx->DR;
		temp = pSPIHandle.pSPIx->SR;
	}
	(void)temp;
	SPI_AppilicationEventCallBack(&pSPIHandle,SPI_EVENT_OVR_ERROR);
}




//SPI PHERIPHERAL CLOCK CONTROLS APIS
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(pSPIx == SPI1)
	{
		if(EnorDi == ENABLE)
		{
			SPI1_PCLK_EN();
		}else
		{
			SPI1_PCLK_DI();
		}
	}else if(pSPIx == SPI2)
	{
		if(EnorDi == ENABLE)
		{
			SPI2_PCLK_EN();
		}else
		{
			SPI2_PCLK_DI();
		}
	}else
	{
		if(EnorDi == ENABLE)
		{
			SPI3_PCLK_EN();
		}else
		{
			SPI3_PCLK_DI();
		}
	}
}


void SPI_Peripheral_EnorDi(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << 6);
	}else
	{
		pSPIx->CR1 &= ~(1 << 6);
	}
}


//SPI INIT AND DEINIT APIS
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t temp1 = 0;



	//PROGRAM THE REGISTER FOR MASTER OR SLAVE MODE
	pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPI_PinConfig.SPI_Device_mode << 2);

	//CHECK FOR FULL DUPLEX COMMUNICATION
	if(pSPIHandle->SPI_PinConfig.SPI_Bus_config == SPI_BUS_2_UNI_DIR)
	{
		temp1 &= ~(pSPIHandle->SPI_PinConfig.SPI_Bus_config << 15);

	}
	//CHECK FOR HALF DUPLEX COMMUNICATION
	else if(pSPIHandle->SPI_PinConfig.SPI_Bus_config == SPI_BUS_1_BI_DIR)
	{
		temp1 |= (pSPIHandle->SPI_PinConfig.SPI_Bus_config << 15);
	}
	//CHECK FOR FULL DUPLEX RECEIVE ONLY
	else
	{
		temp1 |= (pSPIHandle->SPI_PinConfig.SPI_Simplex << 10);
	}
	//CONFIGURE THE SPI SCLK SPEED
	temp1 |= (pSPIHandle->SPI_PinConfig.SPI_Clock_speed << 3);

	//CONFIGURE THE SPI DFF
	temp1 |= (pSPIHandle->SPI_PinConfig.SPI_Data_frame_size << 11);

	//CONFIGURE THE CPOL
	temp1 |= (pSPIHandle->SPI_PinConfig.SPI_CPOL << 1);

	//CONFIGURE THE CPHA
	temp1 |= (pSPIHandle->SPI_PinConfig.SPI_CPHA);

	pSPIHandle->pSPIx->CR1 |= temp1;
}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if(pSPIx == SPI2)
	{
		SPI3_REG_RESET();
	}
}


//ERROR(MAY BE) IN 32 BIT DATA OR 8 BIT DATA
//SPI DATA SEND AND RECEIVE APIS
void SPI_Send_Data(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{	//WAIT FOR TRANSFER BUFFER REGISTER TO BE EMPTY
		if(SPI_GetFlagStatus(pSPIx,SPI_SR_TXE))
		{
			if(pSPIx->CR1 & (1 << 11))
			{
				//DATA IS 16 BIT FORMAT
				//LOAD THE DATA IN DR
				pSPIx->DR = *(uint16_t*)pTxBuffer;
				Len--;
				Len--;
				(uint16_t*)pTxBuffer++;
			}else
			{
				//DATA IS 8 BIT FORMAT
				//LOAD THE DATA IN DR
				pSPIx->DR = *(uint8_t*)pTxBuffer;
				Len--;
				(uint8_t*)pTxBuffer++;
			}
		}
	}
}


void SPI_Recive_Data(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
		if(SPI_GetFlagStatus(pSPIx,SPI_SR_RXNE))
		{
			if(pSPIx->CR1 & (1 << 11))
			{
				//DATA IS 16 FORMAT
				//LOAD THE DATA FROM DR TO RXNE BUFFER
				*((uint16_t*)pRxBuffer) = pSPIx->DR;
				Len--;
				Len--;
				(uint16_t*)pRxBuffer++;
			}else
			{
				//DATA IS 8 FORMAT
				//LOAD THE DATA FROM DR TO RXNE BUFFER
				*((uint8_t*)pRxBuffer) = pSPIx->DR;
				Len--;
				(uint8_t*)pRxBuffer++;
			}
		}
}


//SPI SEND AND RECIVE DATA IN INTERRUPT MODE APIS
/*uint8_t SPI_INTERRUPT_Send_Data(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t State = pSPIHandle->TxState;
	if(State != SPI_Busy_In_Tx)
	{
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;
		pSPIHandle->TxState = SPI_Busy_In_Tx;
		pSPIHandle->pSPIx->CR2 |= (1 << 7);
	}
	return State;
}


uint8_t SPI_INTERRUPT_Recive_Data(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t State = pSPIHandle->RxState;
	if(State != SPI_Busy_In_Rx)
	{
		pRxBuffer = pSPIHandle->pRxBuffer;
		pSPIHandle->RxLen = Len;
		pSPIHandle->RxState = SPI_Busy_In_Rx;
		pSPIHandle->pSPIx->CR2 |= (1 << 6);
	}
	return State;
}*/


//SPI IRQ CONFIGURATION AND ISR HANDLING APIS
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi==ENABLE)
		{
			if(IRQNumber <= 31)
			{
				//PROGRAM ISER0 REGISTER
				*NVIC_ISER0 |= (1 << IRQNumber);
			}
			else if(IRQNumber > 31 && IRQNumber <64 )
			{
				//PROGRAM ISER1 REGISTER
				*NVIC_ISER1 |= (1 << IRQNumber % 32);
			}
			else if(IRQNumber >= 64 && IRQNumber <96 )
			{
				//PROGRAM ISER2 REGISTER
				*NVIC_ISER2 |= (1 << IRQNumber % 64);
			}

		}else
		{
			if(IRQNumber <= 31)
			{
				//PROGRAM ICER0 REGISTER
				*NVIC_ICER0 |= (1 << IRQNumber);
			}
			else if(IRQNumber > 31 && IRQNumber <64 )
			{
				//PROGRAM ICER1 REGISTER
				*NVIC_ICER1 |= (1 << IRQNumber % 32);
			}
			else if(IRQNumber >= 64 && IRQNumber <96 )
			{
				//PROGRAM ICER2 REGISTER
				*NVIC_ICER2 |= (1 << IRQNumber % 64);
			}
		}
}


void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPL);
	*(NVIC_PR_BASEADDR + (iprx * 4)) |= (IRQPriority << shift_amount);
}


void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
		uint8_t temp1, temp2;
		//FIRST CHECK WHAT CAUSE INTERRUPT TO TRIGEER
		temp1 = pSPIHandle->pSPIx->SR & (1 << 1 );
		temp2 = pSPIHandle->pSPIx->CR2 & (1 << 7 );

	if(temp1 && temp2)
	{
		//HANDLE TXE
		SPI_TXNE_Handler(*pSPIHandle);

	}
		temp1 = 0;
		temp2 = 0;
		temp1 = pSPIHandle->pSPIx->SR & (1 );
		temp2 = pSPIHandle->pSPIx->CR2 & (1 << 6 );

	if(temp1 && temp2)
	{
		//HANDLE RXNE
		SPI_RXNE_Handler(*pSPIHandle);

	}

		temp1 = 0;
		temp2 = 0;
		temp1 = pSPIHandle->pSPIx->SR & (1 << 6);
		temp2 = pSPIHandle->pSPIx->CR2 & (1 << 5);

	if(temp1 && temp2)
	{
		//HANDLE OVERRUN
		SPI_OVR_Handler(*pSPIHandle);

	}
}




//SOME OTHER API

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
	    pSPIx->CR1 |= (1 << 8);
	}else
	{
		pSPIx->CR1 &= ~(1 << 8);
	}
}


void SPI_SSMConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
	    pSPIx->CR1 |= (1 << 9);
	}else
	{
		pSPIx->CR1 &= ~(1 << 9);
	}
}


void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
	    pSPIx->CR2 |= (1 << 2);
	}else
	{
		pSPIx->CR2 &= ~(1 << 2);
	}
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return SET;
	}else
	{
		return RESET;
	}

}


void SPI_Clear_OVR_Flag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}


void SPI_Close_Trans(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << 7);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_Ready;
}


void SPI_Close_Rep(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << 6);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_Ready;
}


__attribute__ ((weak)) void SPI_AppilicationEventCallBack(SPI_Handle_t *pSPIHandle , uint8_t AppEV)
{

}





