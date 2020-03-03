#ifndef LP5018
#define LP5018

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LP5018_ADDRESS (0x28)

/////////////////////////////////////////////////////
#define LP5018_DEVICE_CONDIG0 (0x00)

#define LP5018_Chip_EN  (0x40)

/////////////////////////////////////////////////////
#define LP5018_DEVICE_CONFIG1 (0x01)

#define LP5018_Log_Scale_EN (0x20)
#define LP5018_Power_Save_EN (0x10)
#define LP5018_Auto_Incr_EN (0x08)
#define LP5018_PWM_Dithering_EN (0x04)
#define LP5018_Max_Current_Option (0x02)
#define LP5018_LED_Global_Off (0x01)


/////////////////////////////////////////////////////
#define LP5018_LED_CONFIG0 (0x02)

#define LP5018_LED5_Bank_EN (0x20)
#define LP5018_LED4_Bank_EN (0x10)
#define LP5018_LED3_Bank_EN (0x08)
#define LP5018_LED2_Bank_EN (0x04)
#define LP5018_LED1_Bank_EN (0x02)
#define LP5018_LED0_Bank_EN (0x01)


/////////////////////////////////////////////////////
#define LP5018_BANK_BRIGHTNESS (0x03)
#define LP5018_BANK_A_COLOR (0x04)
#define LP5018_BANK_B_COLOR (0x05)
#define LP5018_BANK_C_COLOR (0x06)
#define LP5018_LED0_BRIGHTNESS (0x07)
#define LP5018_LED1_BRIGHTNESS (0x08)
#define LP5018_LED2_BRIGHTNESS (0x09)
#define LP5018_LED3_BRIGHTNESS (0x0A)
#define LP5018_LED4_BRIGHTNESS (0x0B)
#define LP5018_LED5_BRIGHTNESS (0x0C)

typedef enum {
  LP5018_OUT0_COLOR  = 0x0F,
  LP5018_OUT1_COLOR, //0x10
  LP5018_OUT2_COLOR, //0x11
  LP5018_OUT3_COLOR, //0x12
  LP5018_OUT4_COLOR, //0x13
  LP5018_OUT5_COLOR, //0x14
  LP5018_OUT6_COLOR, //0x15
  LP5018_OUT7_COLOR, //0x16
  LP5018_OUT8_COLOR, //0x17
  LP5018_OUT9_COLOR, //0x18
  LP5018_OUT10_COLOR, //0x19
  LP5018_OUT11_COLOR, //0x1A
  LP5018_OUT12_COLOR, //0x1B
  LP5018_OUT13_COLOR, //0x1C
  LP5018_OUT14_COLOR, //0x1D
  LP5018_OUT15_COLOR, //0x1E
  LP5018_OUT16_COLOR, //0x1F
  LP5018_OUT17_COLOR //0x20
} LP5018_OUT;

typedef struct {
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
  uint8_t Brightness;
} LED_type;

uint8_t LP5018_Init();
void LP5018_ALL_ON();
void LP5018_ALL_ON_RED();
void LP5018_ALL_ON_GREEN();
void LP5018_ALL_ON_BLUE();
void LP5018_ALL_OFF();
void LP5018_Set_State(uint8_t R, uint8_t G, uint8_t B, uint8_t Brightness, uint8_t LED_NUMB);
bool LP5018_read_led_state(uint8_t lednum);
void LP5018_toggle(uint8_t lednum);

void LP5018_SetAll(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

#endif