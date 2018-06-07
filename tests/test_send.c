#include "sender.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"

static unsigned long long TEST_BYTE = 0x7effef;

void main() {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    sender_send_scancode(TEST_BYTE);
}
    
