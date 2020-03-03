#include "I2C.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_mtx.h"
#include "nrf_drv_twi.h"
 
const nrf_drv_twi_t m_twi_zero = NRF_DRV_TWI_INSTANCE(0);
static nrf_mtx_t _accessMtx;

void I2C_Init(void) {
    
    uint32_t err_code;

    nrf_mtx_init(&_accessMtx);
    const nrf_drv_twi_config_t twi_zero_config = {
       .scl                = NRF_GPIO_PIN_MAP(1,9),
       .sda                = NRF_GPIO_PIN_MAP(0,8),
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_LOW,
       .clear_bus_init     = false
    };

    while(!nrf_drv_twi_init(&m_twi_zero, &twi_zero_config, NULL, NULL));
    
    nrf_drv_twi_enable(&m_twi_zero);
}

void I2C_Uninit(void){
    nrf_drv_twi_uninit(&m_twi_zero);
}

uint32_t I2C_Write(uint8_t slaveAddr, uint8_t * pData, uint32_t numBytes) {
    while(!nrf_mtx_trylock(&_accessMtx))
    {
        continue;
    }
    uint32_t ret_code = nrf_drv_twi_tx(&m_twi_zero, slaveAddr, pData, numBytes , false);
    nrf_mtx_unlock(&_accessMtx);
    return ret_code;
}

uint32_t I2C_WriteWithStop(uint8_t slaveAddr, uint8_t * pData, uint32_t numBytes) {

    while(!nrf_mtx_trylock(&_accessMtx))
    {
        continue;
    }
    uint32_t ret_code = nrf_drv_twi_tx(&m_twi_zero, slaveAddr, pData, numBytes , true);
    nrf_mtx_unlock(&_accessMtx);
    return ret_code;
}

uint32_t I2C_Read(uint8_t slaveAddr, uint8_t regAddr,  uint8_t * pData, uint32_t numBytes) {
    while(!nrf_mtx_trylock(&_accessMtx))
    {
        continue;
    }
    uint32_t ret_code;

    ret_code = nrf_drv_twi_tx(&m_twi_zero, slaveAddr, &regAddr, 1, true);

    if(ret_code != NRF_SUCCESS)
    {
        nrf_mtx_unlock(&_accessMtx);
        return ret_code;
    }
    ret_code = nrf_drv_twi_rx(&m_twi_zero, slaveAddr, pData, numBytes);
    nrf_mtx_unlock(&_accessMtx);
    return ret_code;
}

uint32_t I2C_Command(uint8_t slaveAddr, uint8_t* command, uint8_t commandLen, uint8_t* data, uint8_t dataLen) {
    while(!nrf_mtx_trylock(&_accessMtx))
    {
        continue;
    }
    uint32_t ret_code = nrf_drv_twi_tx(&m_twi_zero, slaveAddr, command, commandLen , true);
    if (ret_code == 0) {
        ret_code = nrf_drv_twi_rx(&m_twi_zero, slaveAddr, data, dataLen);
    }
    nrf_mtx_unlock(&_accessMtx);
    return ret_code;
}
