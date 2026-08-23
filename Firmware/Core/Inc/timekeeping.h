#ifndef TIMEKEEPING
#define TIMEKEEPING

#include "is31fl3237_driver.h"
#include "stm32u0xx_hal.h"
#include "stm32u0xx_hal_rtc.h"

void TIMEKEEPING_TimeToLedPwm(RTC_TimeTypeDef * time, FL3237_RGB_LED * led_pwms);

void TIMEKEEPING_SetRTCFromString(char * str, uint8_t len);


#endif /* TIMEKEEPING */
