#ifndef SENDER_H
#define SENDER_H

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
 */
void sender_send_code(unsigned int code);

/*
 * Read code from pin using gpio_read
 */

unsigned int sender_read_code(void);

#endif
