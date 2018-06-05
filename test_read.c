#include "sender.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"

void main(void) {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    unsigned long long TEST_BYTE = sender_read_scancode();
    printf("the scancode is: %x", (unsigned int)TEST_BYTE);
}
 
