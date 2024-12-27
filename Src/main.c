
/**
  ******************************************************************************
  * @file		Src/main.c
  * @author		Mateusz Kozłowski & Jacek Maciej Lipiński
  * @brief		Program entry point.
  ******************************************************************************
  * @par			In entry point system clock will be configure, main devices
	* structures will be initialized.
	* Additionally some helper functions will be defined.
	*
  * @bug ...
  *
  ******************************************************************************
  */
////////////////////////////////// Includes ////////////////////////////////////
#include "MainDev.h"

#include "stm32wbxx_ll_system.h"
#include "stm32wbxx_ll_rcc.h"
#include "stm32wbxx_ll_utils.h"
/////////////////////////// Definitions (in module) ////////////////////////////

///////////////// Extern variables and functions declaration  //////////////////
//////////////// Private variables definitions (&declarations) /////////////////
MainDev MainDevOb;
/////////////////////// Private functions declarations /////////////////////////
static void setUpClock(void);
void Error_Handler(uint8_t *file, uint32_t line);
//////////////////////////// Functions definitions /////////////////////////////
int main(void)
{
	setUpClock();
	MainDev_Init(&MainDevOb);
	vTaskStartScheduler();
	for( ;; )
	{
		MainDev_MainLoopProc(&MainDevOb); // If program ends up here sth went wrong and built-in led starts blinking.
	}
}

void vApplicationIdleHook( void )
{
#ifndef DEBUG
	__WFI(); //set core in sleep
#endif
}

/**
  * @brief  This function is executed in system tick
  * @retval None
  */
void vApplicationTickHook( void )
{
	MainDevOb.TickCnt++;
	if(MainDevOb.TickCnt > 0x7FFFFFF)
		MainDevOb.TickCnt = 0;
}

/**
  * @brief  This function is executed in case malloc error.
  * @retval None
  */
void vApplicationMallocFailedHook(void)
{
#ifdef DEBUG
	__ASM volatile("BKPT #01");
#else
#endif
}

/**
  * @brief  This function is executed in case task stack overflow error.
  * @retval None
  */
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
#ifdef DEBUG
	__ASM volatile("BKPT #01");
#else
#endif
}


/**
  * @brief  Configure clocks
  * @retval None
  */

static void setUpClock(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_3)
	{
	}

	/* HSI configuration and activation */
	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1)
	{
	}

	/* MSI configuration and activation */
	LL_RCC_MSI_Enable();
	while(LL_RCC_MSI_IsReady() != 1)
	{
	}

	/* Main PLL configuration and activation */
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 32, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_Enable();
	LL_RCC_PLL_EnableDomain_SYS();
	while(LL_RCC_PLL_IsReady() != 1)
	{
	}

	/* Sysclk activation on the main PLL */
	/* Set CPU1 prescaler*/
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

	/* Set CPU2 prescaler*/
	LL_C2_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}

	/* Set AHB SHARED prescaler*/
	LL_RCC_SetAHB4Prescaler(LL_RCC_SYSCLK_DIV_1);

	/* Set APB1 prescaler*/
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

	/* Set APB2 prescaler*/
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	SystemCoreClockUpdate();

	LL_Init1msTick(SystemCoreClock / 1000);
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(uint8_t *file, uint32_t line)
{
#ifdef DEBUG
	__ASM volatile("BKPT #01");
#else
#endif
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */
#ifdef DEBUG
	__ASM volatile("BKPT #01");
#else
#endif
}
#endif /*USE_FULL_ASSERT*/
