/**
  ******************************************************************************
  * @file		src/I2CDrv.c
  * @author		Wojciech Obrebski
  * @brief		Driver for SPI - methods implementation.
  ******************************************************************************
  * @par			...
  *
  ******************************************************************************
  */

////////////////////////////////// Includes ////////////////////////////////////
#include <stddef.h>

#include "stm32wbxx_ll_bus.h"
#include "stm32wbxx_ll_gpio.h"
#include "stm32wbxx_ll_rcc.h"
#include "stm32wbxx_ll_i2c.h"
#include "stm32wbxx_ll_dma.h"

#include <limits.h>
#include <string.h>
#include "I2CDrv.h"
/////////////////////////// Definitions (in module) ////////////////////////////
///////////////// Extern variables and functions declaration  //////////////////
void Error_Handler(uint8_t *file, uint32_t line);
//////////////// Private variables definitions (&declarations) /////////////////
static I2CDrv *pI2CDrv=NULL;									///< to exchange data with IRQa, additional is a flag that driver is initialized
/////////////////////// Private functions declarations /////////////////////////
static void initGPIO(void);
static void deinitGPIO(void);
static void initI2C(void);
static void deinitI2C(void);
static void initDMA(void);
static void deinitDMA(void);
static void initIRQ(void);
static void deinitIRQ(void);

//////////////////////////// Functions definitions /////////////////////////////

/**
  * @brief		I2CDrv initialization function.
  * @param[in]  this: pointer to \ref I2CDrv object;
  * @retval 	None
  */
void I2CDrv_Init(I2CDrv* this)
{
	this->drvSemph = xSemaphoreCreateBinary();
	if(this->drvSemph == NULL)
		Error_Handler((uint8_t*)__FILE__, __LINE__);
	xSemaphoreGive(this->drvSemph);
	this->intSemph = xSemaphoreCreateBinary();
	if(this->intSemph == NULL)
		Error_Handler((uint8_t*)__FILE__, __LINE__);
	initGPIO();
	initI2C();
	initDMA();
	initIRQ();
	pI2CDrv = this;
}



/**
  * @brief		I2CDrv deinitialization function.
  * @param[in]  this: pointer to \ref I2CDrv object;
  * @retval 	None
  */
void I2CDrv_DeInit(I2CDrv* this)
{
	xSemaphoreTake(this->drvSemph, 100 / portTICK_RATE_MS);
	xSemaphoreTake(this->intSemph, 100 / portTICK_RATE_MS);
	pI2CDrv = NULL;
	deinitIRQ();
	deinitDMA();
	deinitI2C();
	deinitGPIO();

	vSemaphoreDelete( this->drvSemph );
	vSemaphoreDelete( this->intSemph );
}

/**
  * @brief		I2CDrv transaction.
  * @param[in]  this: pointer to \ref I2CDrv object;
  * @param[in]  addr: addres of slave device on bus
  * @param[in]  buff_wr: buffer for data to send
  * @param[in]  no_wr: number of data to send (zero is allowed)
  * @param[in]  buff_rd: buffer for data to receive
  * @param[in]  no_rd: number of data to receive  (zero is allowed)
  * @param[in]  timout: time out [ms]
  * @retval 	\ref I2CDrvRetVal_t
  */
I2CDrvRetVal_t I2CDrv_Transaction(I2CDrv* this, uint8_t addr, uint8_t* buff_wr, uint32_t no_wr, uint8_t* buff_rd, uint32_t no_rd, uint32_t timout)
{
	if(pI2CDrv == NULL)
		return I2CDrvNoInit;
	if((buff_wr == NULL) && (no_wr > 0))
		return I2CDrvWrgArg;
	if((buff_rd == NULL) && (no_rd > 0))
		return I2CDrvWrgArg;
	if( (no_wr + no_rd) == 0)
		return I2CDrvWrgArg;
	if( xSemaphoreTake(this->drvSemph, timout/portTICK_RATE_MS) == pdFALSE)
		return I2CDrvTimout;

	this->retVal = I2CDrvOk;
	//local copy of data to use later in IRQs when state machine need them
	this->addr = addr;
	this->buff_wr = buff_wr;
	this->no_wr = no_wr;
	this->buff_rd = buff_rd;
	this->no_rd = no_rd;

	//I2C1 on DMA1
	//I2C1_RX on Channel 7, Stream 2 or 3
	//I2C1_TX on Channel 7, Stream 7
	//TX
	//Configure DMAs data and length and prepare them to run (DMA is on but in I2C pheryperium it will be turn on in future)
	if(no_wr)
	{
		//DMA TX has one more byte because its include also address
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, no_wr + 1);
		LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)(buff_wr),
				(uint32_t)LL_I2C_DMA_GetRegAddr(I2C1, LL_I2C_DMA_REG_DATA_TRANSMIT),
				LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
		LL_DMA_ClearFlag_TC7(DMA1);
		LL_DMA_ClearFlag_HT7(DMA1);
		LL_DMA_ClearFlag_TE7(DMA1);
		LL_DMA_ClearFlag_FE7(DMA1);
		LL_DMA_ClearFlag_DME7(DMA1);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
	}
	if(no_rd)
	{
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, no_rd);
		LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1,
				(uint32_t)LL_I2C_DMA_GetRegAddr(I2C1, LL_I2C_DMA_REG_DATA_RECEIVE),
				(uint32_t)(buff_rd),
				LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
		LL_DMA_ClearFlag_TC2(DMA1);
		LL_DMA_ClearFlag_HT2(DMA1);
		LL_DMA_ClearFlag_TE2(DMA1);
		LL_DMA_ClearFlag_FE2(DMA1);
		LL_DMA_ClearFlag_DME2(DMA1);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	}

	LL_I2C_Enable(I2C1);
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	LL_I2C_GenerateStartCondition(I2C1);	//this will produce IRQ in I2C when condition will appear on bus

	xSemaphoreTake(this->intSemph,0);
	if (xSemaphoreTake(this->intSemph, timout/portTICK_RATE_MS)==pdFALSE)
	{
		//Timout error, we need clean
		LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
		LL_I2C_DisableDMAReq_TX(I2C1);
		LL_I2C_DisableDMAReq_RX(I2C1);
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
		LL_I2C_Disable(I2C1);
		if(this->retVal == I2CDrvOk)
			this->retVal = I2CDrvTimout;
		xSemaphoreGive(this->drvSemph);
		return this->retVal;
	}
	//ok or error, also need clean. If it is OK then retVal will be set to I2CDrvOk
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
	LL_I2C_DisableDMAReq_TX(I2C1);
	LL_I2C_DisableDMAReq_RX(I2C1);
//	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_7);
//	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
	LL_I2C_Disable(I2C1);
	xSemaphoreGive(this->drvSemph);
	return this->retVal;
}

/**
  * Brief   This function handles I2C1 (Master) interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_EV_IRQHandler(void)
{
	if(pI2CDrv == NULL)
		return;
	if(LL_I2C_IsActiveFlag_SB(I2C1))							//start condition on BUS
	{
		if(pI2CDrv->no_wr)
			LL_I2C_TransmitData8(I2C1, pI2CDrv->addr | 0x00);	//during transmit state, send address and 0x00 as write bit
		else
			LL_I2C_TransmitData8(I2C1, pI2CDrv->addr | 0x01);	//during receive state, send address and 0x01 as read bit
	}
	/* Check ADDR flag value in ISR register */
	else if(LL_I2C_IsActiveFlag_ADDR(I2C1))						//address on bus set and acknowledge
	{
		if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ)	//lets enable DMA RX
		{
			if(pI2CDrv->no_rd == 1)
			{
				 LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
				 LL_I2C_EnableDMAReq_RX(I2C1);
			}
			else if(pI2CDrv->no_rd == 2)
			{
				LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
				LL_I2C_EnableBitPOS(I2C1);
			}
			else
			{
				LL_I2C_EnableLastDMA(I2C1);
				LL_I2C_EnableDMAReq_RX(I2C1);
			}
		}
		else															//lets enable DMA TX
		{
			LL_I2C_EnableDMAReq_TX(I2C1);
		}

		/* Clear ADDR flag value in ISR register */
		LL_I2C_ClearFlag_ADDR(I2C1);
	}
}

/**
  * Brief   This function handles I2C1 (Master) error interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_ER_IRQHandler(void)
{
	if(pI2CDrv == NULL)
		return;
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//	LL_I2C_ClearFlag_AF(I2C1);				//in case ACK Error (eg wrong ADDR)
	LL_I2C_ClearFlag_ARLO(I2C1);			//in case when other master starts transmit
	LL_I2C_ClearFlag_BERR(I2C1);			//in case misplaced start and stop condition
	LL_I2C_ClearFlag_OVR(I2C1);				//in case overrun/underrun condition
	pI2CDrv->retVal = I2CDrvBusErr;
	xSemaphoreGiveFromISR(pI2CDrv->intSemph, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/**
  * @brief  This function handles DMA1 interrupt request (I2C Receiver).
  * @param  None
  * @retval None
  */
void DMA1_Stream2_IRQHandler(void)
{
	if(pI2CDrv == NULL)
		return;

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(LL_DMA_IsActiveFlag_TC2(DMA1))
	{
		LL_DMA_ClearFlag_TC2(DMA1);
		LL_I2C_GenerateStopCondition(I2C1);
		LL_I2C_DisableLastDMA(I2C1);
		xSemaphoreGiveFromISR(pI2CDrv->intSemph, &xHigherPriorityTaskWoken);
	}
	if(LL_DMA_IsActiveFlag_TE2(DMA1))
	{
		LL_DMA_ClearFlag_TE2(DMA1);

		pI2CDrv->retVal = I2CDrvBusErr;
		xSemaphoreGiveFromISR(pI2CDrv->intSemph, &xHigherPriorityTaskWoken);
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/**
  * @brief  This function handles DMA1 interrupt request (I2C Transmiter).
  * @param  None
  * @retval None
  */
void DMA1_Stream7_IRQHandler(void)
{
	if(pI2CDrv == NULL)
		return;
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(LL_DMA_IsActiveFlag_TC7(DMA1))
	{
		LL_DMA_ClearFlag_TC7(DMA1);
		pI2CDrv->no_wr = 0;
		if(pI2CDrv->no_rd == 0)								//there are no data to receive - generate stop
		{
			LL_I2C_GenerateStopCondition(I2C1);
			xSemaphoreGiveFromISR(pI2CDrv->intSemph, &xHigherPriorityTaskWoken);
		}
		else
			LL_I2C_GenerateStartCondition(I2C1);			//ther are also data to receive - restart
	}
	if(LL_DMA_IsActiveFlag_TE7(DMA1))
	{
		LL_DMA_ClearFlag_TE7(DMA1);

		pI2CDrv->retVal = I2CDrvBusErr;
		xSemaphoreGiveFromISR(pI2CDrv->intSemph, &xHigherPriorityTaskWoken);
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

static void initGPIO(void)
{
	//I2C1: SCL on PB10, SDA PB11, AF4
	/* Enable the peripheral clock of GPIO Port */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	/* Configure SCL Pin */
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_4);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);

	/* Configure SDA Pin */
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_4);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_11, LL_GPIO_PULL_UP);

}
static void deinitGPIO(void)
{
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_0);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_0);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ANALOG);
}

static void initI2C(void)
{
	LL_RCC_ClocksTypeDef rcc_clocks;

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
	LL_I2C_Disable(I2C1);

	LL_RCC_GetSystemClocksFreq(&rcc_clocks);
//	LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, I2CDRV_SPEED, LL_I2C_DUTYCYCLE_2);
}

static void deinitI2C(void)
{
	LL_I2C_Disable(I2C1);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
}


static void initDMA(void)
{
	//I2C1: SCL on PB10, SDA PB11, AF4
	//I2C1 on DMA1
	//I2C1_RX on Channel 7, Stream 2 or 3
	//I2C1_TX on Channel 7, Stream 7
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	//DMA for RX
//	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_7, LL_DMA_CHANNEL_4);
	LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_1,
	                        	LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
								LL_DMA_PRIORITY_HIGH              |
								LL_DMA_MODE_NORMAL	              |
								LL_DMA_PERIPH_NOINCREMENT         |
								LL_DMA_MEMORY_INCREMENT           |
								LL_DMA_PDATAALIGN_BYTE            |
								LL_DMA_MDATAALIGN_BYTE);

	//DMA for TX
//	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_7, LL_DMA_CHANNEL_7);
	LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_2,
	                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
	                        LL_DMA_PRIORITY_HIGH              |
	                        LL_DMA_MODE_NORMAL                |
	                        LL_DMA_PERIPH_NOINCREMENT         |
	                        LL_DMA_MEMORY_INCREMENT           |
	                        LL_DMA_PDATAALIGN_BYTE            |
	                        LL_DMA_MDATAALIGN_BYTE);
}

static void deinitDMA(void)
{
	// Później można to podmienić na coś zgodnego z naszym DMA
//	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_7);
//	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
}

static void initIRQ(void)
{
	//I2C
	LL_I2C_EnableIT_EVT(I2C1);
	LL_I2C_EnableIT_ERR(I2C1);

	//DMA RX
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
	//DMA TX
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);

	NVIC_SetPriority(DMA1_Channel1_IRQn, FRTOS_CFG_PREPRIO_I2C + 1);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	NVIC_SetPriority(DMA1_Channel2_IRQn, FRTOS_CFG_PREPRIO_I2C + 1);
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
	NVIC_SetPriority(I2C1_EV_IRQn, FRTOS_CFG_PREPRIO_I2C + 1);
	NVIC_EnableIRQ(I2C1_EV_IRQn);
	NVIC_SetPriority(I2C1_ER_IRQn, FRTOS_CFG_PREPRIO_I2C);
	NVIC_EnableIRQ(I2C1_ER_IRQn);
}

static void deinitIRQ(void)
{
	NVIC_DisableIRQ(I2C1_ER_IRQn);
	NVIC_DisableIRQ(I2C1_EV_IRQn);
	NVIC_DisableIRQ(DMA1_Channel2_IRQn);
	NVIC_DisableIRQ(DMA1_Channel1_IRQn);
}

