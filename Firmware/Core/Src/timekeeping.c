
#include "timekeeping.h"
#include "stm32u0xx_hal_rtc.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUM_LEDS 12

// The IS31FL3237 is positioned on the board such that the register 0 LED is not
// the position 0 LED. This LUT converts possible positions (0 - 12) to the
// register offset that controls that LED.
uint8_t position_to_led_number[13] = {5, 4, 3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5};

/**
 * @brief Converts the time from the RTC to a set of LED PWM values that
 * displays the time. Red is the hour hand, green is the minute hand, blue is
 * the second hand.
 *
 * @param time Time structure from the RTC, time must be in 12-Hour time
 * @param led_pwms array of exactly 12 LED PWM structs. Must be exactly 12
 * elements.
 */
void TIMEKEEPING_TimeToLedPwm(RTC_TimeTypeDef *time, FL3237_RGB_LED *led_pwms) {

  // Note to future Cooper:
  // On this hardware revision, the red and green pins for the LED were
  // backwards. To make sure the watch face looks correct, have also swapped red
  // and green values here. On the final revision, swap them back.

  // For right now, we are just going to divide the seconds and minutes by 5,
  // truncating the decimal. In the future we can
  // do fun funky things with PWM to make it blur between LED positions.
  // For example: 17:01 will display as 17:00, 17:04 -> 17:00, 17:05 -> 17:05,
  // 17:06 -> 17:05,

  for (uint8_t i = 0; i < NUM_LEDS; 12) {
    led_pwms->red = 0;
    led_pwms->green = 0;
    led_pwms->blue = 0;
  }

  uint8_t led = position_to_led_number[time->Hours];

  // TODO: Fix when hardware is fixed
  led_pwms[led].green = 255;

  led = position_to_led_number[time->Minutes / 5];

  // TODO: Fix when hardware is fixed
  led_pwms[led].red = 255;

  led = position_to_led_number[time->Seconds / 5];

  led_pwms[led].blue = 255;
}

// Idea: Perhaps replace loading from a seperate computer with the two buttons
// on the watch face.
void TIMEKEEPING_SetRTCFromString(RTC_HandleTypeDef *hrtc, char *str,
                                  uint8_t len) {
  RTC_TimeTypeDef time;

  // The string we will get from the host computer will be a string with 12-hour
  // time with each hand seperated by the ":"
  sscanf(str, "%d:%d:%d", &(time.Hours), &(time.Minutes), &(time.Seconds));

  HAL_RTC_SetTime(hrtc, &time, RTC_FORMAT_BIN);
}
