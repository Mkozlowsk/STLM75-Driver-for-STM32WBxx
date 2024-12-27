/*
 * MainDev.h
 *
 *  Created on: Mar 2, 2024
 *      Author: panba
 */

#ifndef MAINDEV_H_
#define MAINDEV_H_


////////////////////////////////// Includes ////////////////////////////////////
#include "I2CDrv.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

////////////////////////////// Public definitions //////////////////////////////
////////////////// Public typedefs and structures declarations /////////////////
//////////////////////// Module structure declaration //////////////////////////

/** @brief Main device structure declaration.
* Contains all device functions structures object.
*/
typedef struct _MainDev{
//public:
	uint32_t	TickCnt;	///<counter incremented on every system tick
//privat:
	xTaskHandle	xTask;		///< handle to main working task
	uint8_t 	killTask;	///< set to 1 to kill working task

	I2CDrv		I2CDrvOb;	///< I2CDrv driver object
}MainDev;

///////////////////// Module public methods declaration ////////////////////////
void MainDev_Init(MainDev* this);
void MainDev_DeInit(MainDev* this);
void MainDev_MainLoopProc(MainDev* this);
//static void transmitTask(void *pvParameters);
//static void recieveTask(void *pvParameters);
//static void initGPIO(void);

#endif /*MAINDEV_H_*/

