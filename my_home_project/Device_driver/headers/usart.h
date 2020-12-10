/*
 * usart.s
 *
 *  Created on: 08-May-2020
 *      Author: emes
 */

#ifndef HEADERS_USART_S_
#define HEADERS_USART_S_

#include "stdint.h"
#include "stddef.h"
#include "stm32f4.h"

typedef struct
{
	uint8_t   USART_Mode;
	uint32_t  USART_Baud;
	uint8_t   NoOf_Stop_Bits;
	uint8_t   USART_Word_Len;
	uint8_t   USART_Parity_Control;
	uint8_t   USART_HWF_FLOW_Control;

}USART_Config_t;


typedef struct
{
	USART_Config_t USART_config_t;
	USART_RegDef_t *pUSARTx;
	uint32_t Len;
	uint32_t RxLen;
	uint8_t* pTxBuffer;
	uint8_t* pRxBuffer;
	uint8_t TxBusyState;
	uint8_t RxBusyState;

}USART_Handle_t;




//Possible options for USART_Mode
#define USART_MODE_ONLY_TX 	0
#define USART_MODE_ONLY_RX 	1
#define USART_MODE_TXRX  	2


//Possible options for USART_Baud
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					2400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000




//Possible options for USART_ParityControl
#define USART_PARITY_EN_ODD   	2
#define USART_PARITY_EN_EVEN 	 1
#define USART_PARITY_DISABLE  	 0


//Possible options for USART_WordLength
#define USART_WORDLEN_8BITS 	 0
#define USART_WORDLEN_9BITS 	 1


//Possible options for USART_NoOfStopBits
#define USART_STOPBITS_1    	 0
#define USART_STOPBITS_0_5  	 1
#define USART_STOPBITS_2    	 2
#define USART_STOPBITS_1_5  	 3


//Possible options for USART_HWFlowControl
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3


//USART COMMUNIACTIO STATUS
#define USART_REDY			0
#define USART_BUSY_IN_RX	1
#define USART_BUSY_IN_TX	2

//USART EVENTS
#define USART_EVENT_TX_CMPLT 	1
#define USART_EVENT_RX_CMPLT 	2
#define USART_EVENT_CTS			3
#define USART_EVENT_IDLE		4
#define USART_EVENT_ORE			5


//USART API PROTOTYPE

//USART PHERIPHERAL CLOCK CONTROLS APIS
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);
void USART_Peripheral_EnorDi(USART_RegDef_t *pUSARTx, uint8_t EnorDi);


//USART INIT AND DEINIT APIS
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);
void USART_Set_Baud_Rate(USART_Handle_t *pUSARTHandle, uint32_t Baud_rate);


//USART DATA SEND AND RECIVE APIS
void USART_Send_Data(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len);
void USART_Receive_Data(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len);


//USART DATA SEND AND RECIVE APIS WITH IT
uint8_t USART_Send_DataIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_Receive_DataIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len);

//USART IRQ CONFIGURATION AND ISR HANDLING APIS
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);


//SOME OTHER API
uint8_t USART_GetFlagStatus(USART_RegDef_t *USARTx, uint32_t FlagName);
void USART_AppilicationEventCallBack(USART_RegDef_t *USARTx, uint8_t AppEV);


//USART CR1 BIT DEFINATION
#define USART_CR1_SBK		0
#define USART_CR1_RWU		1
#define USART_CR1_RE		2
#define USART_CR1_TE		3
#define USART_CR1_IDLEIE	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE		7
#define USART_CR1_PEIE		8
#define USART_CR1_PS		9
#define USART_CR1_PCE		10
#define USART_CR1_WAKE		11
#define USART_CR1_M			12
#define USART_CR1_UE		13
#define USART_CR1_OVER8		15


//USART CR2 BIT DEFINATION
#define USART_CR2_ADD		0
#define USART_CR2_LBDL		5
#define USART_CR2_LBDIE		6
#define USART_CR2_LBCL		8
#define USART_CR2_CPHA		9
#define USART_CR2_CPOL		10
#define USART_CR2_CLKEN		11
#define USART_CR2_STOP		12
#define USART_CR2_LINEN		14


//USART CR3 BIT DEFINATION
#define USART_CR3_EIE		0
#define USART_CR3_IREN		1
#define USART_CR3_IRLP		2
#define USART_CR3_HDSEL		3
#define USART_CR3_NACK		4
#define USART_CR3_SCEN		5
#define USART_CR3_DMAR		6
#define USART_CR3_DMAT		7
#define USART_CR3_RTSE		8
#define USART_CR3_CTSE		9
#define USART_CR3_CTSIE		10
#define USART_CR3_ONEBIT	11


//USART SR REGISTER BIT DEFINATION
#define USART_SR_PE		0
#define USART_SR_FE		1
#define USART_SR_NF		2
#define USART_SR_ORE	3
#define USART_SR_IDLE	4
#define USART_SR_RXNE	5
#define USART_SR_TC		6
#define USART_SR_TXE	7
#define USART_SR_LBD	8
#define USART_SR_CTS	9




#endif /* HEADERS_USART_S_ */
