/*
 * i2c.h
 *
 *  Created on: 14-Apr-2020
 *      Author: emes
 */

#ifndef HEADERS_I2C_H_
#define HEADERS_I2C_H_

#include "stm32f4.h"



typedef struct
{
	uint32_t I2C_SCL_Speed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_ACKControl;
	uint16_t I2C_FM_DutyCycle;
}I2C_Config_t;

typedef struct
{
	I2C_RegDef_t 		*pI2Cx;
	I2C_Config_t 		 I2C_Config_t;
	uint8_t 			*pTxBuffer;
	uint8_t			    *pRxBuffer;
	uint32_t 			 TxLen;
	uint32_t 			 RxLen;
	uint32_t 			 Rxsize;
	uint8_t 			 Deviceaddr;
	uint8_t 			 TxRxState;
	uint8_t 			 RS;

}I2C_Handle_t;



//I2C SCLK SPEED
#define I2C_SCL_SPEED_SM	100000
#define I2C_SCL_SPEED_FM	400000


//I2C ACK
#define I2C_ACKControl_EN	1
#define I2C_ACKControl_DI	0


//I2C DUTY CYCLE
#define I2C_FM_DutyCycle_2		0
#define I2C_FM_DutyCycle_16_9	1


//I2C TX RX STATE
#define I2C_READY  		0
#define I2C_BUSY_IN_RX	1
#define I2C_BUSY_IN_TX	2

//I2C APPLICATION EVENT MACRO
#define I2C_EV_TX_CMPLT		0
#define I2C_EV_STOP			1
#define I2C_EV_RX_CMPLT		2

//I2C ERROR MACRO
#define I2C_ERROR_BERR  	3
#define I2C_ERROR_ARLO  	4
#define I2C_ERROR_AF   	 	5
#define I2C_ERROR_OVR   	6
#define I2C_ERROR_TIMEOUT 	7
/*****APIs for I2C******/

//I2C PHERIPHERAL CLOCK CONTROLS APIS
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_Peripheral_EnorDi(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


//I2C INIT AND DEINIT APIS
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

//I2C DATA TRANSFER API
void I2C_Master_SendData(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_Master_ReceiveData(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_Slave_SendData(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len);
void I2C_Slave_ReceiveData(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len);

//I2C DATA TRANSFER API WITH INT
uint8_t I2C_Master_SendDataIT(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr);
uint8_t I2C_Master_ReceiveDataIT(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr);

//I2C IRQ CONFIGURATION AND ISR HANDLING APIS
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

//I2C IRQ HANLDE API
void I2C_EVENT_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ERROR_IRQHandling(I2C_Handle_t *pI2CHandle);

//SOME OTHER API
void I2C_Generate_start(I2C_RegDef_t *pI2Cx);
void I2C_Generate_stop(I2C_RegDef_t *pI2Cx);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_Clear_OVR_Flag(I2C_RegDef_t *pI2Cx);
void I2C_Close_Trans(I2C_Handle_t *pI2CHandle);
void I2C_Close_Rep(I2C_Handle_t *pI2CHandle);
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle , uint8_t AppEV);



//I2C REGISTER BIT DEFINATION

#define I2C_CR1_PE			0
#define I2C_CR1_SMBUS		1
#define I2C_CR1_SMBTYPE		3
#define I2C_CR1_ENARP		4
#define I2C_CR1_ENPEC		5
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_POS			11
#define I2C_CR1_PEC			12
#define I2C_CR1_ALERT		13
#define I2C_CR1_SWRST		15


#define I2C_CR2_FREQ		0
#define I2C_CR2_ITERREN		8
#define I2C_CR2_ITEVTEN		9
#define I2C_CR2_ITBUFEN		10
#define I2C_CR2_DMAEN		11
#define I2C_CR2_LAST		12


#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RxNE		6
#define I2C_SR1_TxE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALERT	15


#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_SMBDEFAULT	5
#define I2C_SR2_SMBHOST		6
#define I2C_SR2_PEC			7





#endif /* HEADERS_I2C_H_ */
