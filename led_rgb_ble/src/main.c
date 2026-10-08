
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, 3);

#ifdef CONFIG_LAMB_RGB_LED
    #include "led/led.h"

    void led_fade_test()
    {
        const int steps = 50;
        const int delay_ms = 10;
        const led_color_t led = LED_BLUE;

        // smooth green fade in/out
        for (int cycle = 0; cycle < 4; cycle++) {
            // Fade in: ease-in-out
            for (int i = 0; i <= steps; i++) {
                float t = (float) i / steps;
                // Ease-in-out quadratic
                float eased = t < 0.5f ? 2.0f * t * t : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
                uint8_t level = (uint8_t) (eased * 50.0f);
                led_fade_control(led, level);
                k_msleep(delay_ms);
            }
    
            // Fade out: ease-in-out
            for (int i = 0; i <= steps; i++) {
                float t = (float) i / steps;
                float eased = t < 0.5f ? 2.0f * t * t : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
                uint8_t level = (uint8_t) ((1.0f - eased) * 70.0f);
                led_fade_control(led, level);
                k_msleep(delay_ms);
            }
        }
        k_msleep(10);
        set_led_off();
        k_msleep(10);

    }
#endif 

int main(void)
{

    printk("Starting Program...\n");

#ifdef CONFIG_LAMB_RGB_LED
    int ret;

    ret = led_start();
    if (ret){
        LOG_ERR("Failed to initialize LEDs");
        return ret;
    }

    led_fade_test();

    k_msleep(2000);

    set_led_custom(255,255,0);

    k_msleep(2000);

    while (led_cmd_testing) {
        printk("RED LED\n");
        set_led_red();   /* Red */
        k_msleep(1000);
        
        printk("BLUE LED\n");
        set_led_blue();
        k_msleep(1000);
        
        printk("GREEN LED\n");
        set_led_green();
        k_msleep(1000);

        printk("OFF LED\n");
        set_led_off();
        k_msleep(1000);
    }
#else
    LOG_WRN("Lamb RGB LED is disabled.");
#endif

    return 0;
}