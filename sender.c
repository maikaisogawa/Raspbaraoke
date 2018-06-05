#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "sender.h"

static unsigned int TX_PIN, RX_PIN, DELAY_US;

/*
static void setup_interrupts(void) {
    bool ok = interrupts_attach_handler(interrupt_read_scancode);
    if (!ok) pi_abort();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
    interrupts_global_enable();
}
*/

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
 * function: send_bit
 * Sets TX_PIN to high or low for DELAY_US microseconds
 * @param a - 1 or 0 (if not 1 or 0, does nothing)
 */
void send_bit(unsigned char a) {
    gpio_write(TX_PIN, a);
    timer_delay_us(DELAY_US);
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
        char bit = scancode & 1;
        scancode >>= 1;
        send_bit(bit);
    }
    send_bit(1); //stop bit
}

void sender_send_code(unsigned long long  code) {
    while (code) {
        unsigned int scancode = code & 0xff;
        code >>= 8;
        send_byte(scancode); 
    } 
}

/*
 * function: read_byte
 * Reads eight bits from RX_PIN and returns the value of that eight-bit
 * binary number.
 */
unsigned int read_byte(void) {
    unsigned int READ_BYTE = 0;
    while (gpio_read(RX_PIN)) {} //wait for start bit 
    for (int i = 0; i < 8; i++) {
        timer_delay_us(DELAY_US);
        READ_BYTE = READ_BYTE + (gpio_read(RX_PIN) << i);
    }
    //timer_delay_us(DELAY_US);
    return READ_BYTE;
} 
unsigned long long sender_read_code(void) {
    unsigned long long code = 0;
    unsigned int byte;
    int offset = 0;
    while (1) {
        byte = read_byte();
        code = code | (read_byte() << offset);
        offset += 8;
        if (byte == 0xef) break;
    }
    return code;
}
