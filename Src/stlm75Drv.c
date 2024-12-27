#include "stlm75Drv.h"


static STLM75Drv *pSTLM75Drv = NULL;


void I2C_sendByte(STLM75Drv *this, uint8_t reg, uint8_t sendByte){
	uint8_t writeBuf[2];
	writeBuf[0] = reg;
	writeBuf[1] = sendByte;
	I2CDrv_Transaction(&this->i2cDrv, STLM75_ADDRESS, writeBuf,2,writeBuf,0,200); //Przesyła najpierw bajt pointera na rejestr, potem bajt danych do wskazanego rejestru
}
void I2C_send2Bytes(STLM75Drv *this, uint8_t reg, uint16_t sendByte){
	uint8_t writeBuf[3];
	writeBuf[0] = reg;
	writeBuf[1] = (uint8_t)((sendByte >> 8) & 0xFF);	//rozdzielenie uint16_t na dwa 8bitowe bajty w celu przesłania (źle ujęte)
	writeBuf[2] = (uint8_t)(sendByte & 0xFF);			//najpierw przesyłany jest najważniejszy bajt
	I2CDrv_Transaction(&this->i2cDrv, STLM75_ADDRESS, writeBuf,2,writeBuf,0,200); //Przesyła najpierw bajt pointera na rejestr, potem bajt danych do wskazanego rejestru
}

void I2C_readByte(STLM75Drv *this, uint8_t reg){
	uint8_t writeBuf[1];
	writeBuf[0] = reg;
	I2CDrv_Transaction(&this->i2cDrv, STLM75_ADDRESS | 0x01, writeBuf,1,this->readBuf,1,200); //Przesyła bajt pointera na rejestr, następnie odbiera dwa bajty danych (wszystkei rejestry peryferium z ktorych sie czyta maja 2 bajty)
}
void I2C_read2Bytes(STLM75Drv *this, uint8_t reg){
	uint8_t writeBuf[1];
	writeBuf[0] = reg;
	I2CDrv_Transaction(&this->i2cDrv, STLM75_ADDRESS | 0x01, writeBuf,1,this->readBuf,2,200); //Przesyła bajt pointera na rejestr, następnie odbiera dwa bajty danych (wszystkei rejestry peryferium z ktorych sie czyta maja 2 bajty)
}

void STLM75_Init(STLM75Drv *this, I2CDrv pi2cDrv)
{
	pSTLM75Drv = this;
	this->i2cDrv = pi2cDrv;
	this->conversionMode = STLM75_CONTINUOUS_MODE;
	this->operationMode = STLM75_COMPARATOR_MODE;
	this->hysteresisTemp = 0x50; //ustawienie temperatury histerezy na 80 stopni
	this->pwrTemp = 0x55; //ustawienie temperatury power down na 85 stopni
	I2C_sendByte(this,STLM75_REG_CONF ,this->operationMode | this->conversionMode); //Ustawienie trybu operacji i konwersji
	I2C_send2Bytes(this,LM75_REG_THYS,this->hysteresisTemp);
	I2C_send2Bytes(this,LM75_REG_TOS,this->pwrTemp);
}


float STLM75_ReadTemp(STLM75Drv *this)
{

	I2C_read2Bytes(this, STLM75_REG_TEMP);
	uint8_t temp1 = this->readBuf[0];
	uint8_t temp2 = this->readBuf[1];

	uint16_t result = ((uint16_t)temp1 << 8) | temp2;
	return (float)(result);
}
