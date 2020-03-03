#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//#include "Config.h"
#include <stdint.h>

void I2C_Init(void);

void I2C_Uninit(void);

uint32_t I2C_Write(uint8_t slaveAddr, uint8_t * pData, uint32_t numBytes);
uint32_t I2C_WriteWithStop(uint8_t slaveAddr, uint8_t * pData, uint32_t numBytes);

uint32_t I2C_Read(uint8_t slaveAddr, uint8_t regAddr,  uint8_t * pData, uint32_t numBytes);
uint32_t I2C_Command(uint8_t slaveAddr, uint8_t* command, uint8_t commandLen, uint8_t* data, uint8_t dataLen);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_INCLUDED */