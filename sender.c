#include "gpio.h"
#include "gpioextra.h"
#include "timer.h"
#include "sender.h"
#include "printf.h"

#define START_CODE 0x7e
 
static unsigned int TX_PIN, RX_PIN, DELAY_US;

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
    
    printf("setup done.TX Pin: %x\n", gpio_read(TX_PIN)); 
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
 * Transmitted in little-endian form. 
 * @param scancode - 1-byte number to be sent through serial protocol
 */
void send_byte(unsigned char scancode) {
    send_bit(0); //start bit
    unsigned int written = 0; 
    unsigned int sent_code = 0;
    unsigned int received_code = 0;
    for (int i = 0; i < 8; i++) {
        char bit = scancode & 1;
        scancode >>= 1;
        send_bit(bit);
    }
    send_bit(1); //stop bit
}

void sender_send_code(unsigned char* code, int size) {
    printf("sending ");
    for (int i = 0; i < size; i++) {
        printf("%02x", code[i]);
    } 
    printf("\n");
    printf("tx pin: %x\n", gpio_read(TX_PIN));
    for (int i = 0; i < size; i++) {
        send_byte(code[i]);
    } 
}

/*
 * function: read_byte
 * Reads eight bits from RX_PIN and returns the value of that eight-bit
 * binary number (read in little-endian format). 
 */
unsigned int read_byte(void) {
    unsigned int READ_BYTE = 0;
    while (gpio_read(RX_PIN)) {} //wait for start bit 
    for (int i = 0; i < 8; i++) {
        timer_delay_us(DELAY_US);
        READ_BYTE = READ_BYTE + (gpio_read(RX_PIN) << i);
    }
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
        if (byte == START_CODE) break; //(stop reading)
    }
    return code;
}
