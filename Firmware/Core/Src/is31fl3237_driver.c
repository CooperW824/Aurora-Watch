#include "is31fl3237_driver.h"
#include "stm32u0xx_hal_gpio.h"
#include "stm32u0xx_hal_i2c.h"
#include <stdint.h>
#include <string.h>

#define HIGH_BYTE_MASK 0xFF00
#define LOW_BYTE_MASK 0x00FF

void FL3237_Init(FL3237_HandleTypeDef *handle) {
  // Set shutdown pin to output and set it high to enable the chip
  HAL_GPIO_WritePin(handle->shutdown_port, handle->pin, GPIO_PIN_SET);
}

void FL3237_SetControlRegister(FL3237_HandleTypeDef *handle,
                               FL3237_ControlRegisterConfig crc) {
  uint8_t command = 0x00 | (crc.osc << 4) | (crc.pms << 1) | (crc.ssd);
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x00,
                    I2C_MEMADD_SIZE_8BIT, &command, 1,
                    handle->max_transmit_timeout_ms);
}

void FL3237_SetHardwareChipEnable(FL3237_HandleTypeDef *handle,
                                  GPIO_PinState state) {
  HAL_GPIO_WritePin(handle->shutdown_port, handle->pin, state);
}

void FL3237_SetPWM(FL3237_HandleTypeDef *handle, uint8_t led_number,
                   FL3237_RGB_LED pwm) {
  // The FL3237 has 72 registers for RGB PWM values, starting at 0x01. Each
  // LED has 6 registers (RL, RH, GL, GH, BL, BH), so the register for a given
  // LED can be calculated as 0x01 + (led_number * 6). This code assumes using
  // 8-bit PWM values, so the high byte for each color is set to 0x00.
  uint8_t data[6] = {
      (pwm.red & LOW_BYTE_MASK),   ((pwm.red & HIGH_BYTE_MASK) >> 8),
      (pwm.green & LOW_BYTE_MASK), ((pwm.green & HIGH_BYTE_MASK) >> 8),
      (pwm.blue & LOW_BYTE_MASK),  ((pwm.blue & HIGH_BYTE_MASK) >> 8)};

  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x01 + (led_number * 6),
                    I2C_MEMADD_SIZE_8BIT, data, 6,
                    handle->max_transmit_timeout_ms);
}

FL3237_RGB_LED FL3237_GetPWM(FL3237_HandleTypeDef *handle, uint8_t led_number) {
  uint8_t data[6];

  HAL_I2C_Mem_Read(handle->i2c_bus, handle->address, 0x01 + (led_number * 6),
                   I2C_MEMADD_SIZE_8BIT, data, 6,
                   handle->max_transmit_timeout_ms);

  FL3237_RGB_LED led;
  led.red = data[0] | (data[1] << 8);
  led.green = data[2] | (data[3] << 8);
  led.blue = data[4] | (data[5] << 8);

  return led;
}

void FL3237_UpdatePWM(FL3237_HandleTypeDef *handle) {
  uint8_t command =
      0x00; // Write 0x00 to Register 0x49 to update PWM for all registers.
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x49,
                    I2C_MEMADD_SIZE_8BIT, &command, 1,
                    handle->max_transmit_timeout_ms);
}

void FL3237_SetGlobalCurrent(FL3237_HandleTypeDef *handle, uint8_t gcc) {
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x6E,
                    I2C_MEMADD_SIZE_8BIT, &gcc, 1,
                    handle->max_transmit_timeout_ms);
}

void FL3237_SetLEDScaling(FL3237_HandleTypeDef *handle, uint8_t led_number,
                          FL3237_LED_SCALE scale) {
  uint8_t data[] = {scale.red, scale.green, scale.blue};
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x4A + (led_number * 3),
                    I2C_MEMADD_SIZE_8BIT, data, 3,
                    handle->max_transmit_timeout_ms);
}

FL3237_LED_SCALE FL3237_GetLEDScaling(FL3237_HandleTypeDef *handle,
                                      uint8_t led_number) {
  uint8_t data[3];
  HAL_I2C_Mem_Read(handle->i2c_bus, handle->address, 0x4A + (led_number * 3),
                   I2C_MEMADD_SIZE_8BIT, data, 3,
                   handle->max_transmit_timeout_ms);

  FL3237_LED_SCALE scale;
  scale.red = data[0];
  scale.green = data[1];
  scale.blue = data[2];

  return scale;
}

void FL3237_SetAllScaling(FL3237_HandleTypeDef *handle,
                          FL3237_LED_SCALE scale) {
  uint8_t data[36];
  for (uint8_t i = 0; i < 12; i++) {
    data[i * 3] = scale.red;
    data[i * 3 + 1] = scale.green;
    data[i * 3 + 2] = scale.blue;
  }

  // 4Ah is OUT1's scaling register; 36 consecutive registers cover OUT1..OUT36
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x4A,
                    I2C_MEMADD_SIZE_8BIT, data, 36,
                    handle->max_transmit_timeout_ms);
}
