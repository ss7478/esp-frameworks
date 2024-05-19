#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "lib.h"

int channels[38];
int modes[38];
int cur_channel = 0;
int cur_mode = 1;

void define_pwm_pin(int pin, int freq)  //Use this function as an analog of pinMode.
{                                       //This function defines a pin to generate pwm with specified frequency.
    // Prepare and then apply the LEDC PWM timer configuration
    if(cur_channel > 7)
    {   
        cur_mode = 0;
        cur_channel = 0;
    }
    modes[pin] = cur_mode;
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = modes[pin],
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = cur_mode,
        .freq_hz          = freq,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
    
    channels[pin]=cur_channel;
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = modes[pin],
        .channel        = channels[pin],
        .timer_sel      = cur_mode,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pin,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    cur_channel++;
}

void write_pwm(int pin, int duty)   //Use this function as an analog of analogWrite.
{                                   //This function generates PWM with a specified duty on a specified pin.
    ledc_set_duty(modes[pin], channels[pin], duty);            
    ledc_update_duty(modes[pin], channels[pin]);
}