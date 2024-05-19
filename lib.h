#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               1
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_12_BIT

void define_pwm_pin(int pin, int freq);  //pin definition function
void write_pwm(int pin, int duty);  //function which generates PWM with specified duty