#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "sender.h"

static const unsigned int TX_PIN, RX_PIN, BAUD_RATE; 

void sender_init(unsigned int tx_pin, unsigned int rx_pin, 
    unsigned int baud_rate) {
    RX_PIN = rx_pin;
    TX_PIN = tx_pin;
    BAUD_RATE = baud_rate;
}

void send_code(unsigned int code) {
    double DELAY_US = (1.0/BAUD_RATE)*1000000.0;
    while (code) {
        unsigned int scancode = code & 0xff;
        code >> 8;
}

unsigned int read_code(void) {

}
