#include sender.h
#include gpio.h
#include gpioextra.h
#include printf.h

static unsigned long long TEST_BYTE = 0xFF;

main() {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    TEST_BYTE = sender_read_scancode();
    printf("the scancode is: %x", (unsigned int)TEST_BYTE);
}
 
