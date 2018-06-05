#include "sender.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"

static unsigned long long TEST_BYTE = 0x7e0541000045ef;

void main(void) {
    gpio_set_input(GPIO_PIN24);
    gpio_set_pulldown(GPIO_PIN24);
    printf("before init, reading: %x\n", gpio_read(GPIO_PIN24));
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    printf("after init, reading: %x\n", gpio_read(GPIO_PIN24));
    sender_send_code(TEST_BYTE);
    printf("after sending code, reading: %x\n", gpio_read(GPIO_PIN24));
}
    
