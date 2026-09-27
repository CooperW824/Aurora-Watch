#include "lsm303agr.h"

HAL_StatusTypeDef LSM303_Accel_SetControlRegs(LSM303_HandleTypeDef *handle) {}

HAL_StatusTypeDef LSM303_Accel_Enable(LSM303_HandleTypeDef *handle) {}
HAL_StatusTypeDef LSM303_Accel_Disable(LSM303_HandleTypeDef *handle) {}

HAL_StatusTypeDef LSM303_Accel_IsDataReady(LSM303_HandleTypeDef *handle,
                                         uint8_t *ready) {}
HAL_StatusTypeDef LSM303_Accel_ReadData(LSM303_HandleTypeDef *handle,
                                        LSM303_Int16Vec3 *out) {}

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
