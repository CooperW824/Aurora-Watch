#ifndef LSM303AGR_DRIVER
#define LSM303AGR_DRIVER

#include "stm32u031xx.h"
#include "stm32u0xx_hal.h"
#include "stm32u0xx_hal_i2c.h"
#include <stdint.h>

#define LSM303_ACCEL_ADDR 0b00110010
#define LSM303_MAG_ADDR 0b00111100

/* ============================================================
 * Register Addresses
 * ============================================================ */

/* --- Accelerometer registers (00h-3Fh) --- */
#define LSM303_REG_STATUS_AUX_A 0x07
#define LSM303_REG_OUT_TEMP_L_A 0x0C
#define LSM303_REG_OUT_TEMP_H_A 0x0D
#define LSM303_REG_INT_COUNTER_A 0x0E
#define LSM303_REG_WHO_AM_I_A 0x0F
#define LSM303_REG_TEMP_CFG_A 0x1F
#define LSM303_REG_CTRL_REG1_A 0x20
#define LSM303_REG_CTRL_REG2_A 0x21
#define LSM303_REG_CTRL_REG3_A 0x22
#define LSM303_REG_CTRL_REG4_A 0x23
#define LSM303_REG_CTRL_REG5_A 0x24
#define LSM303_REG_CTRL_REG6_A 0x25
#define LSM303_REG_REFERENCE_A 0x26
#define LSM303_REG_STATUS_REG_A 0x27
#define LSM303_REG_OUT_X_L_A 0x28
#define LSM303_REG_OUT_X_H_A 0x29
#define LSM303_REG_OUT_Y_L_A 0x2A
#define LSM303_REG_OUT_Y_H_A 0x2B
#define LSM303_REG_OUT_Z_L_A 0x2C
#define LSM303_REG_OUT_Z_H_A 0x2D
#define LSM303_REG_FIFO_CTRL_A 0x2E
#define LSM303_REG_FIFO_SRC_A 0x2F

/* --- Magnetometer registers (40h-6Fh) --- */
#define LSM303_REG_OFFSET_X_L_M 0x45
#define LSM303_REG_OFFSET_X_H_M 0x46
#define LSM303_REG_OFFSET_Y_L_M 0x47
#define LSM303_REG_OFFSET_Y_H_M 0x48
#define LSM303_REG_OFFSET_Z_L_M 0x49
#define LSM303_REG_OFFSET_Z_H_M 0x4A
#define LSM303_REG_WHO_AM_I_M 0x4F
#define LSM303_REG_CFG_REG_A_M 0x60
#define LSM303_REG_CFG_REG_B_M 0x61
#define LSM303_REG_CFG_REG_C_M 0x62
#define LSM303_REG_INT_CTRL_M 0x63
#define LSM303_REG_INT_SOURCE_M 0x64
#define LSM303_REG_INT_THS_L_M 0x65
#define LSM303_REG_INT_THS_H_M 0x66
#define LSM303_REG_STATUS_REG_M 0x67
#define LSM303_REG_OUTX_L_M 0x68
#define LSM303_REG_OUTX_H_M 0x69
#define LSM303_REG_OUTY_L_M 0x6A
#define LSM303_REG_OUTY_H_M 0x6B
#define LSM303_REG_OUTZ_L_M 0x6C
#define LSM303_REG_OUTZ_H_M 0x6D

#define LSM303_WHO_AM_I_A_VALUE 0x33
#define LSM303_WHO_AM_I_M_VALUE 0x40

/* ============================================================
 * CTRL_REG1_A (20h): ODR3 ODR2 ODR1 ODR0 | LPen Zen Yen Xen
 * ============================================================ */
#define LSM303_A_XEN (1U << 0)
#define LSM303_A_YEN (1U << 1)
#define LSM303_A_ZEN (1U << 2)
#define LSM303_A_LPEN (1U << 3)

#define LSM303_A_ODR_POWERDOWN (0x0U << 4)
#define LSM303_A_ODR_1HZ (0x1U << 4)
#define LSM303_A_ODR_10HZ (0x2U << 4)
#define LSM303_A_ODR_25HZ (0x3U << 4)
#define LSM303_A_ODR_50HZ (0x4U << 4)
#define LSM303_A_ODR_100HZ (0x5U << 4)
#define LSM303_A_ODR_200HZ (0x6U << 4)
#define LSM303_A_ODR_400HZ (0x7U << 4)
#define LSM303_A_ODR_1620HZ_LP (0x8U << 4) /* low-power mode only */
#define LSM303_A_ODR_1344HZ (0x9U << 4)    /* HR/Normal; 5376 Hz in LP mode */

/* ============================================================
 * CTRL_REG4_A (23h): BDU BLE FS1 FS0 HR ST1 ST0 SPI_ENABLE
 * ============================================================ */
#define LSM303_A_SPI_ENABLE (1U << 0)
#define LSM303_A_HR (1U << 3)
#define LSM303_A_BLE (1U << 6)
#define LSM303_A_BDU (1U << 7)

#define LSM303_A_ST_NORMAL (0x0U << 1)
#define LSM303_A_ST_0 (0x1U << 1)
#define LSM303_A_ST_1 (0x2U << 1)

#define LSM303_A_FS_2G (0x0U << 4)
#define LSM303_A_FS_4G (0x1U << 4)
#define LSM303_A_FS_8G (0x2U << 4)
#define LSM303_A_FS_16G (0x3U << 4)

/* ============================================================
 * CTRL_REG5_A (24h): BOOT FIFO_EN -- -- LIR_INT1 D4D_INT1 LIR_INT2 D4D_INT2
 * ============================================================ */
#define LSM303_A_D4D_INT2 (1U << 0)
#define LSM303_A_LIR_INT2 (1U << 1)
#define LSM303_A_D4D_INT1 (1U << 2)
#define LSM303_A_LIR_INT1 (1U << 3)
#define LSM303_A_FIFO_EN (1U << 6)
#define LSM303_A_BOOT (1U << 7)

/* ============================================================
 * CFG_REG_A_M (60h): COMP_TEMP_EN REBOOT SOFT_RST LP ODR1 ODR0 MD1 MD0
 * ============================================================ */
#define LSM303_M_COMP_TEMP_EN (1U << 7) /* must be 1 per datasheet note */
#define LSM303_M_REBOOT (1U << 6)
#define LSM303_M_SOFT_RST (1U << 5)
#define LSM303_M_LP (1U << 4)

#define LSM303_M_ODR_10HZ (0x0U << 2)
#define LSM303_M_ODR_20HZ (0x1U << 2)
#define LSM303_M_ODR_50HZ (0x2U << 2)
#define LSM303_M_ODR_100HZ (0x3U << 2)

#define LSM303_M_MODE_CONTINUOUS 0x0U
#define LSM303_M_MODE_SINGLE 0x1U
#define LSM303_M_MODE_IDLE 0x2U /* 0x3 also valid, same as 0x2 */

/* ============================================================
 * CFG_REG_B_M (61h): 000 OFF_CANC_ONE_SHOT INT_on_DataOFF Set_FREQ OFF_CANC LPF
 * ============================================================ */
#define LSM303_M_LPF (1U << 0)
#define LSM303_M_OFF_CANC (1U << 1)
#define LSM303_M_SET_FREQ (1U << 2)
#define LSM303_M_INT_ON_DATAOFF (1U << 3)
#define LSM303_M_OFF_CANC_ONE_SHOT (1U << 4)

/* ============================================================
 * CFG_REG_C_M (62h): 0 INT_MAG_PIN I2C_DIS BDU BLE 0 Self_test INT_MAG
 * ============================================================ */
#define LSM303_M_INT_MAG (1U << 0) /* not in struct; DRDY as digital output */
#define LSM303_M_SELF_TEST (1U << 1)
/* bit 2 reserved, must be 0 */
#define LSM303_M_BLE (1U << 3)
#define LSM303_M_BDU (1U << 4)
#define LSM303_M_I2C_DIS (1U << 5)
#define LSM303_M_INT_MAG_PIN (1U << 6) /* not in struct */

typedef struct {

  // Control Register 1
  uint8_t odr;
  uint8_t low_power;
  uint8_t z_enable;
  uint8_t y_enable;
  uint8_t x_enable;

  // CR2 Skipped: Not Needed

  // CR3 Skipped: Not Needed

  // CR4
  uint8_t block_data_update;
  uint8_t endianess;
  uint8_t scale_selection;
  uint8_t operating_mode;
  uint8_t self_test;
  uint8_t spi_enable;

  // CR5
  uint8_t boot;
  uint8_t fifo_enable;
  // Rest of CR5 Skipped

  // CR6 Skipped: Not needed
} LSM303_AccelConfigTypeDef;

typedef struct {
  // CR1
  uint8_t temperature_compensation_enable;
  uint8_t reboot;
  uint8_t soft_rst;
  uint8_t low_power;
  uint8_t output_data_rate;
  uint8_t mode;

  // CR2
  // The Interupt Configuration bits were skipped

  uint8_t one_shot_offset_cancelation_enable;
  uint8_t set_pulse_frequency;
  uint8_t offset_cancelation_enable;
  uint8_t low_pass_filter_enable;

  // CR3
  // The Interupt Configuration bits were skipped

  uint8_t i2c_disable;
  uint8_t block_data_update;
  uint8_t endianess;
  uint8_t self_test;
} LSM303_MagConfigTypeDef;

typedef struct {
  I2C_HandleTypeDef *i2c_bus;
  uint8_t accel_address;
  uint8_t mag_address;
  LSM303_AccelConfigTypeDef *accel_cfg;
  LSM303_MagConfigTypeDef *mag_cfg;

} LSM303_HandleTypeDef;

typedef struct {
  int16_t x;
  int16_t y;
  int16_t z;
} LSM303_Int16Vec3;

HAL_StatusTypeDef LSM303_Accel_SetControlRegs(LSM303_HandleTypeDef *handle);

HAL_StatusTypeDef LSM303_Accel_Enable(LSM303_HandleTypeDef *handle);
HAL_StatusTypeDef LSM303_Accel_Disable(LSM303_HandleTypeDef *handle);

HAL_StatusTypeDef LSM303_Mag_IsDataReady(LSM303_HandleTypeDef *handle,
                                         uint8_t *ready);
HAL_StatusTypeDef LSM303_Accel_ReadData(LSM303_HandleTypeDef *handle,
                                        LSM303_Int16Vec3 *out);

HAL_StatusTypeDef LSM303_Mag_SetControlRegs(LSM303_HandleTypeDef *handle);

HAL_StatusTypeDef LSM303_Mag_Enable(LSM303_HandleTypeDef *handle);
HAL_StatusTypeDef LSM303_Mag_Disable(LSM303_HandleTypeDef *handle);

HAL_StatusTypeDef LSM303_Mag_ReadData(LSM303_HandleTypeDef *handle,
                                      LSM303_Int16Vec3 *out);
HAL_StatusTypeDef LSM303_Mag_IsDataReady(LSM303_HandleTypeDef *handle,
                                         uint8_t *ready);

HAL_StatusTypeDef LSM303_Mag_GetHardIronOffset(LSM303_HandleTypeDef *handle,
                                               LSM303_Int16Vec3 *offset);
HAL_StatusTypeDef LSM303_Mag_SetHardIronOffset(LSM303_HandleTypeDef *handle,
                                               const LSM303_Int16Vec3 *offset);

#endif /* LSM303AGR_DRIVER */
