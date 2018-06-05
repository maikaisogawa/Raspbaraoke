#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "sender.h"

static const unsigned int TX_PIN, RX_PIN, DELAY_US;

void sender_init(unsigned int tx_pin, unsigned int rx_pin, 
    unsigned int baud_rate) {
    RX_PIN = rx_pin;
    TX_PIN = tx_pin;
    DELAY_US = 1000000/baud_rate;
    
    //configure RX
    gpio_set_input(RX_PIN);
    gpio_set_pulldown(RX_PIN);

    //configure TX
    gpio_set_output(TX_PIN);
    gpio_write(TX_PIN, 1);
}

/*
 * function: send_byte
 * Sends a byte formatted according to the BY8301-16P voice module serial
 * protocol:Start bit: 1 (high); data bits: 8; Parity: None; 
 *     Stop Bits: 1 (low). 
 * @param scancode - 1-byte number to be sent through serial protocol
 */
void send_byte(unsigned int scancode) {
    send_bit(0); //start bit
    for (int i = 0; i < 8; i++) {
        bit = scancode & 1;
        scancode >> 1;
        send_bit(bit);
    }
    gpio_write(TX_PIN, 1); //stop bit
}

/*
 * function: send_bit
 * Sets TX_PIN to high or low for DELAY_US microseconds
 * @param a - 1 or 0 (if not 1 or 0, does nothing)
 */
void send_bit(unsigned char a) {
    gpio_write(TX_PIN, a);
    timer_delay_us(DELAY_US);
}

void send_code(unsigned int code) {
    while (code) {
        unsigned int scancode = code & 0xff;
        code >>= 8;
        send_byte(scancode); 
    } 
}

unsigned int read_code(void) {

}
