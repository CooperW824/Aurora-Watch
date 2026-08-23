#include "tmp1075_driver.h"
#include "stm32u0xx_hal.h"
#include "stm32u0xx_hal_i2c.h"

void TMP1075_Init(TMP1075_HandleTypeDef *handle) {
  uint8_t data[2] = {0x01, 0x00};
  // Put the device immediately into the one-shot standby mode
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x01,
                    I2C_MEMADD_SIZE_16BIT, data, 1, handle->timeout_ms);
}

int16_t TMP1075_OneShot(TMP1075_HandleTypeDef *handle) {
  uint8_t cmd[2] = {0x81, 0x00};
  HAL_I2C_Mem_Write(handle->i2c_bus, handle->address, 0x01,
                    I2C_MEMADD_SIZE_16BIT, cmd, 1, handle->timeout_ms);

  uint8_t data[2];

  HAL_Delay(25);

  HAL_I2C_Mem_Read(handle->i2c_bus, handle->address, 0x00,
                   I2C_MEMADD_SIZE_16BIT, data, 2, handle->timeout_ms);

  return (data[0] << 8 | data[1]);
}
