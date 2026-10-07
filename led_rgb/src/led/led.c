#include "led.h"

static const struct device *leds = DEVICE_DT_GET(DT_NODELABEL(pwmleds));

int led_start(void)
{
    if (!device_is_ready(leds)) {
        printk("Error: PWM LED parent device is not ready\n");
        return -1;
    }

    return 0;
}

void set_led_custom(uint8_t r, uint8_t g, uint8_t b)
{
    led_set_brightness(leds, 0, (r * 100) / 255);
    led_set_brightness(leds, 1, (b * 100) / 255);
    led_set_brightness(leds, 2, (g * 100) / 255);
}

void led_fade_control(led_color_t color, uint8_t level)
{

    if(level > 100) level = 100;

    switch (color) {
        case LED_RED:
            led_set_brightness(leds, 0, (255 * level) / 255);
            led_set_brightness(leds, 1, 0);
            led_set_brightness(leds, 2, 0);
            break;
        case LED_GREEN:
            led_set_brightness(leds, 0, 0);
            led_set_brightness(leds, 1, 0);
            led_set_brightness(leds, 2, (255 * level) / 255);
            break;
        case LED_BLUE:
            led_set_brightness(leds, 0, 0);
            led_set_brightness(leds, 1, (255 * level) / 255);
            led_set_brightness(leds, 2, 0);
            break;
        default:
            printk("Invalid LED color");
            return;
    }
}

void set_led_red()
{
    led_set_brightness(leds, 0, 100);
    led_set_brightness(leds, 1, 0);
    led_set_brightness(leds, 2, 0);
}

void set_led_blue()
{
    led_set_brightness(leds, 0, 0);
    led_set_brightness(leds, 1, 100);
    led_set_brightness(leds, 2, 0);
}

void set_led_green()
{
    led_set_brightness(leds, 0, 0);
    led_set_brightness(leds, 1, 0);
    led_set_brightness(leds, 2, 100);
}

void set_led_off()
{
    led_set_brightness(leds, 0, 0);
    led_set_brightness(leds, 1, 0);
    led_set_brightness(leds, 2, 0);
}