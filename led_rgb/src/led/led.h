#ifndef LED_H
#define LED_H

#include <zephyr/kernel.h>
#include <zephyr/drivers/led.h>

typedef enum{
  LED_RED,
  LED_GREEN,
  LED_BLUE
} led_color_t;

int led_start();
void set_led_red();
void set_led_green();
void set_led_blue();
void set_led_custom(uint8_t r, uint8_t g, uint8_t b);
void led_fade_control(led_color_t color, uint8_t level);
void set_led_off();

#endif