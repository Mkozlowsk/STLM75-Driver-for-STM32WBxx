
#include "I2CDrv.h"

#define STLM75_ADDRESS								((uint8_t)0x90) //Adres peryferium gdy wszystkie piny adresowe są pullniete do 0 (być może na płytce jest inaczej)


#define STLM75_CONTINUOUS_MODE                 		((uint8_t)0x00)
#define STLM75_ONE_SHOT_MODE                    	((uint8_t)0x01)


#define STLM75_COMPARATOR_MODE                  	((uint8_t)0x00)
#define STLM75_INTERRUPT_MODE                   	((uint8_t)0x02)

#define STLM75_REG_TEMP       	0x00  // Rejestr temperatury
#define STLM75_REG_CONF       	0x01  // Rejestr konfiguracyjny
#define LM75_REG_THYS       	0x02  // Rejestr histerezy default 70 stopni
#define LM75_REG_TOS        	0x03  // Rejestr wylaczenia przy przegrzaniu default 80 stopni



typedef struct _STLM75Drv{
		I2CDrv i2cDrv;
		uint8_t readBuf[2];
		uint8_t conversionMode;
		uint8_t operationMode;
		uint16_t hysteresisTemp;
		uint16_t pwrTemp;
}STLM75Drv;

void I2C_sendByte(STLM75Drv *this, uint8_t reg, uint8_t sendByte);
void I2C_readByte(STLM75Drv *this, uint8_t reg);
void I2C_send2Bytes(STLM75Drv *this, uint8_t reg, uint16_t sendByte);
void I2C_read2Bytes(STLM75Drv *this, uint8_t reg);

void                      STLM75_Init(STLM75Drv *this, I2CDrv pi2cDrv);
float                     STLM75_ReadTemp(STLM75Drv *this);
