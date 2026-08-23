#ifndef TMP1075_DRIVER
#define TMP1075_DRIVER

#include "stm32u0xx_hal.h"

typedef struct {
  I2C_HandleTypeDef *i2c_bus;
  uint8_t address;
  uint32_t timeout_ms;
} TMP1075_HandleTypeDef;

void TMP1075_Init(TMP1075_HandleTypeDef *handle);

/*
Note to future Cooper:

The sensor is positioned such that the LEDs can noticiably influence the sensor's reading, up to 8 degrees C above the ambient air temperature.
I will be moving the sensor and isolating its ground planes on the final hardware revision to mitigate this issue.  
For the ambient air thermometer function, read the the temperature when the watch first starts up and store it in RAM
 before starting up the IS31FL3237 or any of the LEDs to get the most accurate temperature.
 
 This will mean that the thermometer isn't live updating, but honestly I don't think it needs to be.
*/
int16_t TMP1075_OneShot(TMP1075_HandleTypeDef *handle);

#endif /* TMP1075_DRIVER */
