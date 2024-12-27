/**
  ******************************************************************************
  * @file			Inc/I2CDrv.h
  * @author		Wojciech Obrebski
  * @brief		Driver for SPI.
  ******************************************************************************
  * @par			Krotki opis przedimplementacyjny
  * I2C jest magistrala stanowa wiec nie da sie tego wprost obsluzyc w DMA - DMA oplaca sie uzywac tylko
  * w welobajtowych transmisjach. Stany magistrali zaleza od trybu (one lub multimaster) i strony (master lub slave)
  * i tutaj obsluguje tylko wersje pojedynczego mastera i od strony mastera. Stany magistrali obslugiwane sa
  * w przerywaniach a transmija danych (poza adresem) w DMA. Test byl wykonany dla czujnika LPS25HB i płytki
  * Kamami KA-NUCLEO-MULTISENSOR
    ******************************************************************************
  */
#ifndef I2CDRV_H_
#define I2CDRV_H_

////////////////////////////////// Includes ////////////////////////////////////
#include "stm32wbxx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
////////////////////////////// Public definitions //////////////////////////////
#define I2CDRV_SPEED		( 400000 )													///< I2C bus speed


typedef enum
{
	I2CDrvOk,																			///< Ok
	I2CDrvErr,																			///< other Error
	I2CDrvBsy,																			///< driver busy
	I2CDrvTimout,																		///< time out
	I2CDrvNoInit,																		///< driver not initialized
	I2CDrvWrgArg,																		///< wrong function arguments
	I2CDrvBusErr,																		///< I2C bus error
}I2CDrvRetVal_t;																		///< returned

////////////////// Public typedefs and structures declarations /////////////////
//////////////////////// Module structure declaration //////////////////////////

/** @brief Main device structure declaration.
* Contains all device functions structures object.
*/
typedef struct _I2CDrv
{
//public:
//privat:
	SemaphoreHandle_t	drvSemph;													///< driver busy semaphor
	SemaphoreHandle_t	intSemph;													///< internal lock (to wait for DMA finish) semaphor

	uint8_t 			addr;														///< actual operation slave address
	uint8_t* 			buff_wr;													///< actual operation write buffer address
	uint32_t 			no_wr;														///< actual operation write buffer length
	uint8_t* 			buff_rd;													///< actual operation read buffer address
	uint32_t 			no_rd;														///< actual operation read buffer length
	I2CDrvRetVal_t		retVal;														///< actual operation redVal;
}I2CDrv;

///////////////////// Module public methods declaration ////////////////////////
void I2CDrv_Init(I2CDrv* this);
void I2CDrv_DeInit(I2CDrv* this);

I2CDrvRetVal_t I2CDrv_Transaction(I2CDrv* this, uint8_t addr, uint8_t* buff_wr, uint32_t no_wr, uint8_t* buff_rd, uint32_t no_rd, uint32_t timout);

#endif /*I2CDRV_H_*/
