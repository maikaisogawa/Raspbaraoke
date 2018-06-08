#ifndef SENDER_H
#define SENDER_H

struct instruction {
    unsigned char* code;
    int size;
};

/*
 * Functions for sending scancodes from the Raspberry Pi
 *
 * Author: Callan Hoskins, Gen Singer, Maika Isogawa
 * 4 June 2018
 */

/*
 * function: sender_init
 * Initializes global variables
 * @param tx_pin - pin that should be used to transmit
 * @param rx_pin - pin that should be read from
 */
void sender_init(unsigned int tx_pin, unsigned int rx_pin, 
    unsigned int baud_rate);
/*
 * Send code from pin using gpio_write
 * @param code - code to be sent, in the form of an array of bytes
 * @param size - number of elements in array code
 */
void sender_send_code(unsigned char* code, int size);

/*
 * Read code from pin using gpio_read
 */

unsigned long long sender_read_code(void);

#endif
