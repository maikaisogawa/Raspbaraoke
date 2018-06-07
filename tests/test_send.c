#include "sender.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "timer.h"

static unsigned long long TEST_BYTE = 0x7e030102ef;
#define PLAY 0x7E030102EF
#define STOP 0x7E030E0DEF
#define SETUP 0x7E0541000145EF

void main() {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    gpio_write(GPIO_PIN23, 0);
    timer_delay_ms(230);
    gpio_write(GPIO_PIN24, 1);
    /*
    sender_send_code(SETUP);
    sender_send_code(PLAY);
    sender_send_code(STOP);    
    */
}
    
