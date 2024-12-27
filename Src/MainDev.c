/**
  ******************************************************************************
  * @file		src/MainDev.c
  * @author		Mateusz Kozłowski & Jacek Maciej Lipiński
  * @brief		Main Device - methods implementation.
  ******************************************************************************
  * @par			...
  *
  ******************************************************************************
  */

////////////////////////////////// Includes ////////////////////////////////////
#include "MainDev.h"
#include "stm32wbxx_ll_bus.h"
#include "stm32wbxx_ll_gpio.h"

/////////////////////////// Definitions (in module) ////////////////////////////
///////////////// Extern variables and functions declaration  //////////////////
void Error_Handler(uint8_t *file, uint32_t line);
//////////////// Private variables definitions (&declarations) /////////////////
static MainDev *pMainDev = NULL;
/////////////////////// Private functions declarations /////////////////////////
//////////////////////////// Functions definitions /////////////////////////////

/**
  * @brief		MainDev initialization function.
  * @param[in]  this: pointer to \ref MainDev object;
  * @retval 	None
  */
void MainDev_Init(MainDev* this)
{
	pMainDev = this;
	this->TickCnt = 0;

}

/**
  * @brief		MainDev deinitialization function.
	* For MainDev it is only template because it will be never call
  * @param[in]  this: pointer to \ref MainDev object;
  * @retval 	None
  */
void MainDev_DeInit(MainDev* this)
{

}

//static void transmitTask(void *pvParameters){
//	MainDev* this = (MainDev*) pvParameters;
//	USARTDrv_Init(&this -> usartDrv);
//
//	while(!this->killTransmitTask)
//		{
//			DMA_Channel2_IRQHandler();
//		}
//	this->uartTransmitTask = NULL;
//	vTaskDelete( NULL );
//
//}


//static void recieveTask(void *pvParameters){
//	MainDev* this = (MainDev*) pvParameters;
//
//	USARTDrv_Init(&this -> usartDrv);
//	while(!this->killRecieveTask)
//		{
//			DMA_Channel1_IRQHandler();
//		}
//	this->uartRecieveTask = NULL;
//	vTaskDelete( NULL );
//}

static void initGPIO(void){
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_0, LL_GPIO_AF_0);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_0, LL_GPIO_PULL_NO);

}

/**
  * @brief		Class processing loop.
  * Insert in main loop
  * @param[in]  this: pointer to \ref MainDev object;
  * @retval 	None
  */
void MainDev_MainLoopProc(MainDev* this)
{
	pMainDev = this;
	initGPIO();
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_0);
}

