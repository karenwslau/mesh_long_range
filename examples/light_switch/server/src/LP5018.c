//#include "Config.h"

#if HW_VERSION_MINOR == 3
#include "LP5018.h"
#include "I2C.h"
#include "nrf_log.h"

#include "nrf.h"
#include "nrf_error.h"
#include "nrf_gpio.h"
#include "Timers.h"

#include "nrf_delay.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static char tempBuff[50];
char LP5018_config_0;
char LP5018_config_1;
char LED_config0 = 0;
char LED_I2C_TX_BUFFER_1B[2];
char LED_I2C_TX_BUFFER[18];
char LED_I2C_RX_BUFFER[18];
char LED_BRIGHTNESS[7];
char LED_R[7];
char LED_G[7];
char LED_B[7];

void LP5018_WriteMulti(uint8_t reg, uint8_t* value, uint8_t size);
void LP5018_Write8(uint8_t reg, uint8_t value);
void LP5018_CLEAR_ALL_COLOUR_REG();
uint8_t LP5018_read_bank_status();

uint8_t LP5018_Init()
{
  //Config 0 - Enable Chip
  
  LP5018_config_0 = LP5018_Chip_EN;
  LED_I2C_TX_BUFFER[0] = LP5018_config_0;
  LP5018_config_1 = (LP5018_Power_Save_EN | LP5018_Auto_Incr_EN);
  LED_I2C_TX_BUFFER[1] = LP5018_config_1;
  nrf_delay_ms(20);
  LP5018_WriteMulti( LP5018_DEVICE_CONDIG0, LED_I2C_TX_BUFFER, 2);
  nrf_delay_ms(10);
  LED_config0 = LP5018_read_bank_status();
  LP5018_CLEAR_ALL_COLOUR_REG();
  return LED_I2C_RX_BUFFER[0];
}

void LP5018_Write8(uint8_t reg, uint8_t value) {
  //uint8_t dataBytes[2] = {reg, value};
  uint8_t dataBytes[2];
  LED_I2C_TX_BUFFER_1B[0] = reg;
  LED_I2C_TX_BUFFER_1B[1] = value;
  uint32_t ret_code = I2C_Write(LP5018_ADDRESS, LED_I2C_TX_BUFFER_1B, sizeof(LED_I2C_TX_BUFFER_1B));
  if(ret_code != 0){
      memset(tempBuff, '\0', sizeof(tempBuff));
      NRF_LOG_INFO("I2C Write Error! err_code = %d (%s) LP5018 \n", ret_code, tempBuff);
  }
}

void LP5018_WriteMulti(uint8_t reg, uint8_t* value, uint8_t size) {
  uint8_t i = 1;
  uint8_t dataBytes[20];
  dataBytes[0] = reg;
  for(i = 1; i<=size; i++)
  {
    dataBytes[i] = *value;
    value++;
  }
  uint32_t ret_code = I2C_Write(LP5018_ADDRESS, dataBytes, i);
  if(ret_code != 0){
      //memset(tempBuff, '\0', sizeof(tempBuff));
      //get_readable_error_message((uint32_t)ret_code, tempBuff, sizeof(tempBuff));
      NRF_LOG_INFO("I2C Write Error! err_code = %d LP5018 \n", ret_code);
  }
}

void LP5018_ALL_ON()
{
  LED_config0 =  (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
  LED_I2C_TX_BUFFER[0] = LED_config0;
  LED_I2C_TX_BUFFER[1] =  0xff;   // LP5018_BANK_BRIGHTNESS 0x03
  LED_I2C_TX_BUFFER[2] =  0xff;   // LP5018_BANK_A_COLOR 0x04 b
  LED_I2C_TX_BUFFER[3] =  0xff;   // LP5018_BANK_B_COLOR 0x05 r
  LED_I2C_TX_BUFFER[4] =  0xff;   // LP5018_BANK_C_COLOR 0x06 g
  LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}

void LP5018_ALL_ON_BLUE()
{
  LED_config0 = (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
  LED_I2C_TX_BUFFER[0] = LED_config0;
  LED_I2C_TX_BUFFER[1] =  0xff;   // LP5018_BANK_BRIGHTNESS 0x03
  LED_I2C_TX_BUFFER[2] =  0xff;   // LP5018_BANK_A_COLOR 0x04 b
  LED_I2C_TX_BUFFER[3] =  0x00;   // LP5018_BANK_B_COLOR 0x05 r
  LED_I2C_TX_BUFFER[4] =  0x00;   // LP5018_BANK_C_COLOR 0x06 g
  LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}

void LP5018_ALL_ON_RED()
{
  LED_config0 = (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
  LED_I2C_TX_BUFFER[0] = LED_config0;
  LED_I2C_TX_BUFFER[1] =  0xff;   // LP5018_BANK_BRIGHTNESS 0x03
  LED_I2C_TX_BUFFER[2] =  0x00;   // LP5018_BANK_A_COLOR 0x04 b
  LED_I2C_TX_BUFFER[3] =  0xff;   // LP5018_BANK_B_COLOR 0x05 r
  LED_I2C_TX_BUFFER[4] =  0x00;   // LP5018_BANK_C_COLOR 0x06 g
  LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}

void LP5018_ALL_ON_GREEN()
{
  LED_config0 = (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
  LED_I2C_TX_BUFFER[0] = LED_config0;
  LED_I2C_TX_BUFFER[1] =  0xff;   // LP5018_BANK_BRIGHTNESS 0x03
  LED_I2C_TX_BUFFER[2] =  0x00;   // LP5018_BANK_A_COLOR 0x04 b
  LED_I2C_TX_BUFFER[3] =  0x00;   // LP5018_BANK_B_COLOR 0x05 r
  LED_I2C_TX_BUFFER[4] =  0xff;   // LP5018_BANK_C_COLOR 0x06 g
  LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}


void LP5018_ALL_OFF()
{
  LED_config0 = (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
  LED_I2C_TX_BUFFER[0] = LED_config0;
  LED_I2C_TX_BUFFER[1] =  0x00;   // LP5018_BANK_BRIGHTNESS 0x03
  LED_I2C_TX_BUFFER[2] =  0x00;   // LP5018_BANK_A_COLOR 0x04
  LED_I2C_TX_BUFFER[3] =  0x00;   // LP5018_BANK_B_COLOR 0x05
  LED_I2C_TX_BUFFER[4] =  0x00;   // LP5018_BANK_C_COLOR 0x06
  LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}

void LP5018_CLEAR_ALL_COLOUR_REG()
{
  for(uint8_t i = 0; i<18; i++)
  {
    LED_I2C_TX_BUFFER[i] = 0;
  } //Clear the LED I2C buffer
  LP5018_WriteMulti(LP5018_BANK_BRIGHTNESS, LED_I2C_TX_BUFFER, 10);
  LP5018_WriteMulti(LP5018_LED0_BRIGHTNESS, LED_I2C_TX_BUFFER, 6);
  LP5018_WriteMulti(LP5018_OUT0_COLOR, LED_I2C_TX_BUFFER, 18);
}

void LP5018_Set_State(uint8_t R, uint8_t G, uint8_t B, uint8_t Brightness, uint8_t LED_NUMB)
{
  uint8_t first_led_addr = LP5018_OUT0_COLOR + ( LED_NUMB * 3);
  uint8_t brightness_addr = LP5018_LED0_BRIGHTNESS + LED_NUMB;
  uint8_t new_bank_status = 1 <<LED_NUMB;
  if(LED_config0 & new_bank_status)
  {
    LED_config0 = LED_config0 ^ new_bank_status;
  }
  LP5018_Write8(LP5018_LED_CONFIG0, LED_config0);
  LP5018_Write8(brightness_addr, Brightness);
  LED_I2C_TX_BUFFER[0] = B;
  LED_I2C_TX_BUFFER[1] = R;
  LED_I2C_TX_BUFFER[2] = G;
  LP5018_WriteMulti(first_led_addr, LED_I2C_TX_BUFFER, 3);
};

void LP5018_SetAll(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
{
    LED_config0 = (LP5018_LED4_Bank_EN | LP5018_LED3_Bank_EN |  LP5018_LED2_Bank_EN | LP5018_LED1_Bank_EN | LP5018_LED0_Bank_EN);
    LED_I2C_TX_BUFFER[0] = LED_config0;
    LED_I2C_TX_BUFFER[1] =  brightness;
    LED_I2C_TX_BUFFER[2] =  blue;
    LED_I2C_TX_BUFFER[3] =  red;
    LED_I2C_TX_BUFFER[4] =  green;
    LP5018_WriteMulti(LP5018_LED_CONFIG0, LED_I2C_TX_BUFFER, 5);
}

bool LP5018_read_led_state(uint8_t lednum)
{
  uint8_t regAddr = LP5018_LED0_BRIGHTNESS + lednum;
  uint8_t bank_flag = 1;
  uint32_t ret_code = I2C_Read(LP5018_ADDRESS, 2,  LED_I2C_RX_BUFFER, 1);
  if(ret_code != 0){
      NRF_LOG_INFO("I2C Read Error! err_code = %d LP5018 \n", ret_code);
  }

    bank_flag = bank_flag << lednum;
  if(LED_I2C_RX_BUFFER[0] & bank_flag)  //Check to see if the led is bank enabled (i.e. controlled by 1 set of brightness and colour registers)
  {
    ret_code = I2C_Read(LP5018_ADDRESS, LP5018_BANK_BRIGHTNESS,  LED_I2C_RX_BUFFER, 1);
  } else {
    ret_code = I2C_Read(LP5018_ADDRESS, regAddr,  LED_I2C_RX_BUFFER, 1);
  }
  
  if(ret_code != 0){
      NRF_LOG_INFO("I2C Read Error! err_code = %d LP5018 \n", ret_code);
  }
  if(LED_I2C_RX_BUFFER[0]>0)
    return 1;
  else
    return 0;
}

uint8_t LP5018_read_bank_status()
{
  uint32_t ret_code = I2C_Read(LP5018_ADDRESS, LP5018_LED_CONFIG0,  LED_I2C_RX_BUFFER, 1);
  if(ret_code != 0){
      NRF_LOG_INFO("I2C Read Error! err_code = %d LP5018 \n", ret_code);
  }
  return LED_I2C_RX_BUFFER[0];
}

void LP5018_toggle(uint8_t lednum)
{
  
  if(LP5018_read_led_state(lednum)>0)
    LP5018_Set_State(0x00, 0x00, 0x00, 0x00, lednum );
  else
    LP5018_Set_State(0xff, 0xff, 0xff, 0xff, lednum );
}
#endif