#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"

#define DATA_PIN GPIO_PIN18

void readPin(void) {
    gpio_set_function(DATA_PIN, GPIO_FUNC_INPUT);
    gpio_set_pulldown(DATA_PIN);
    while (1) {
        if (gpio_read(DATA_PIN)) {
            printf("1\n");
        }
    }
}
    

void main(void) {
    readPin(); 
}
