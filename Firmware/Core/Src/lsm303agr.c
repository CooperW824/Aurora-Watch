#include "lsm303agr.h"
#include "stm32u0xx_hal_def.h"
#include "stm32u0xx_hal_i2c.h"
#include <stdint.h>

#define LSM303_A_DATA_READY_MASK (1 << 3)

HAL_StatusTypeDef LSM303_Accel_SetControlRegs(LSM303_HandleTypeDef *handle) {
  uint8_t data[2] = {0, 0};

  // Enable temperature sensor
  data[0] = (0b11 << 6);

  HAL_StatusTypeDef status = HAL_I2C_Mem_Write(
      handle->i2c_bus, handle->accel_address << 1, LSM303_REG_TEMP_CFG_A,
      I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);

  if (status != HAL_OK)
    return status;

  // We leave the CR1 at reset value since that is used to enable / disable the
  // device Skipping CR2 & CR3

  // Setting CR4 & CR5
  data[0] = 0;
  data[0] |=
      (handle->accel_cfg->block_data_update | handle->accel_cfg->endianess |
       handle->accel_cfg->scale_selection | handle->accel_cfg->operating_mode |
       handle->accel_cfg->self_test | handle->accel_cfg->spi_enable);

  data[1] = handle->accel_cfg->fifo_enable;

  status = HAL_I2C_Mem_Write(handle->i2c_bus, handle->accel_address << 1,
                             LSM303_REG_CTRL_REG4_A, I2C_MEMADD_SIZE_8BIT, data,
                             2, HAL_MAX_DELAY);
  return status;
}

HAL_StatusTypeDef LSM303_Accel_Enable(LSM303_HandleTypeDef *handle) {
  uint8_t data = handle->accel_cfg->odr | handle->accel_cfg->low_power |
                 handle->accel_cfg->x_enable | handle->accel_cfg->y_enable |
                 handle->accel_cfg->z_enable;

  return HAL_I2C_Mem_Write(handle->i2c_bus, handle->accel_address << 1,
                           LSM303_REG_CTRL_REG1_A, I2C_MEMADD_SIZE_8BIT, &data,
                           1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef LSM303_Accel_Disable(LSM303_HandleTypeDef *handle) {
  uint8_t data = 0;
  return HAL_I2C_Mem_Write(handle->i2c_bus, handle->accel_address << 1,
                           LSM303_REG_CTRL_REG1_A, I2C_MEMADD_SIZE_8BIT, &data,
                           1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef LSM303_Accel_IsDataReady(LSM303_HandleTypeDef *handle,
                                           uint8_t *ready) {
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
      handle->i2c_bus, handle->accel_address << 1, LSM303_REG_STATUS_REG_A,
      I2C_MEMADD_SIZE_8BIT, ready, 1, HAL_MAX_DELAY);
  *ready &= LSM303_A_DATA_READY_MASK;
  return status;
}

HAL_StatusTypeDef LSM303_Accel_ReadData(LSM303_HandleTypeDef *handle,
                                        LSM303_Int16Vec3 *out) {

  if (out == NULL)
    return HAL_ERROR;

  uint8_t data[6] = {0, 0, 0, 0, 0, 0};

  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
      handle->i2c_bus, handle->accel_address << 1, LSM303_REG_OUT_X_L_A,
      I2C_MEMADD_SIZE_8BIT, data, 6, HAL_MAX_DELAY);

  uint8_t num_bits;

  if (handle->accel_cfg->low_power == LSM303_A_LP_ENABLE) {
    num_bits = 8;
  } else if (handle->accel_cfg->operating_mode == LSM303_A_LR) {
    num_bits = 10;
  } else {
    num_bits = 12;
  }

  int16_t raw =
      (int16_t)((data[0] << 8) | data[1]); // cast to signed BEFORE shifting
  out->x = raw >> (16 - num_bits);
  raw = (int16_t)((data[2] << 8) | data[3]); // cast to signed BEFORE shifting
  out->y = raw >> (16 - num_bits);
  raw = (int16_t)((data[4] << 8) | data[5]); // cast to signed BEFORE shifting
  out->z = raw >> (16 - num_bits);
  return status;
}

HAL_StatusTypeDef LSM303_Mag_SetControlRegs(LSM303_HandleTypeDef *handle) {}

HAL_StatusTypeDef LSM303_Mag_Enable(LSM303_HandleTypeDef *handle) {}
HAL_StatusTypeDef LSM303_Mag_Disable(LSM303_HandleTypeDef *handle) {}

HAL_StatusTypeDef LSM303_Mag_ReadData(LSM303_HandleTypeDef *handle,
                                      LSM303_Int16Vec3 *out) {}
HAL_StatusTypeDef LSM303_Mag_IsDataReady(LSM303_HandleTypeDef *handle,
                                         uint8_t *ready) {}

HAL_StatusTypeDef LSM303_Mag_GetHardIronOffset(LSM303_HandleTypeDef *handle,
                                               LSM303_Int16Vec3 *offset) {}
HAL_StatusTypeDef LSM303_Mag_SetHardIronOffset(LSM303_HandleTypeDef *handle,
                                               const LSM303_Int16Vec3 *offset) {

}
