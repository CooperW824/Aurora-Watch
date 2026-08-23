/**
 * @file fl3237_driver.h
 * @author Cooper Werner (cooperwerner824@gmail.com)
 * @brief A Simple I2C driver for the FL3237 from Lumissil Systems
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 */

#ifndef FL3237_DRIVER_H
#define FL3237_DRIVER_H

#include "stm32u031xx.h"
#include "stm32u0xx_hal.h"
#include "stm32u0xx_hal_gpio.h"
#include "stm32u0xx_hal_i2c.h"
#include <stdint.h>

#define FL3237_I2C_AD_TO_GND 0b01101000
#define FL3237_I2C_AD_TO_VCC 0b01101110
#define FL3237_I2C_AD_TO_SCL 0b01101010
#define FL3237_I2C_AD_TO_SDA 0b01101100

#define FL3237_HARDWARE_CHIP_ENABLE GPIO_PIN_SET
#define FL3237_HARDWARE_CHIP_DISABLE GPIO_PIN_RESET

typedef struct {
  I2C_HandleTypeDef *i2c_bus;
  GPIO_TypeDef *shutdown_port;
  uint16_t pin;
  uint8_t address;
  uint32_t max_transmit_timeout_ms;
} FL3237_HandleTypeDef;

#define FL3237_SSD_SHUTDOWN 0x00
#define FL3237_SSD_CHIP_ENABLE 0x01

#define FL3237_PMS_8_BIT 0
#define FL3237_PMS_10_BIT 1
#define FL3237_PMS_12_BIT 2
#define FL3237_PMS_16_BIT 3

#define FL3237_OSC_16_MHZ 0
#define FL3237_OSC_8_MHZ 1
#define FL3237_OSC_1_MHZ 2
#define FL3237_OSC_500_KHZ 3
#define FL3237_OSC_250_KHZ 4
#define FL3237_OSC_125_KHZ 5
#define FL3237_OSC_62_KHZ 6
#define FL3237_OSC_31_KHZ 7

typedef struct {
  // Software Shutdown either FL3237_SSD_SHUTDOWN or FL3237_SSD_CHIP_ENABLE
  uint8_t ssd;
  // PWM Resolution
  uint8_t pms;
  // Oscillator Clock Frequency
  uint8_t osc;
} FL3237_ControlRegisterConfig;

typedef struct {
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} FL3237_RGB_LED;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} FL3237_LED_SCALE;

void FL3237_Init(FL3237_HandleTypeDef *handle);

void FL3237_SetControlRegister(FL3237_HandleTypeDef *handle,
                               FL3237_ControlRegisterConfig crc);

void FL3237_SetHardwareChipEnable(FL3237_HandleTypeDef *handle,
                                  GPIO_PinState state);

void FL3237_SetPWM(FL3237_HandleTypeDef *handle, uint8_t led_number,
                   FL3237_RGB_LED pwm);

void FL3237_BulkSetPWM(FL3237_HandleTypeDef *handle, uint8_t start_led,
                       FL3237_RGB_LED *pwms, uint8_t len);

FL3237_RGB_LED FL3237_GetPWM(FL3237_HandleTypeDef *handle, uint8_t led_number);

void FL3237_UpdatePWM(FL3237_HandleTypeDef *handle);

void FL3237_SetGlobalCurrent(FL3237_HandleTypeDef *handle, uint8_t gcc);

void FL3237_SetLEDScaling(FL3237_HandleTypeDef *handle, uint8_t led_number,
                          FL3237_LED_SCALE scale);

FL3237_LED_SCALE FL3237_GetLEDScaling(FL3237_HandleTypeDef *handle,
                                      uint8_t led_number);

void FL3237_SetAllScaling(FL3237_HandleTypeDef *handle, FL3237_LED_SCALE scale);

#endif /* FL3237_DRIVER_H */
