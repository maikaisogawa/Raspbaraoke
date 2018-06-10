#include "sender.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "timer.h"

static unsigned long long TEST_BYTE = 0x7e030102ef;
//#define PLAY 0x7E030102EF
//#define STOP 0x7E030E0DEF
//#define SETUP 0x7E0541000145EF

const struct instruction PLAY = {{0x7e, 0x03, 0x01, 0x02, 0xef}, 5};
const struct instruction STOP = {{0x7e, 0x03, 0x0e, 0x0d, 0xef}, 5};
const struct instruction SETUP = {{0x7e, 0x05, 0x41, 0x00, 0x01, 0x45,
    0xef}, 7};

void main() {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    unsigned char setup[8] = {0x7e, 0x05, 0x41, 0x00, 0x01, 0x45,
    0xef};
    /*
    printf("stp 0: %x, 1: %x, 2: %x, 3: %x, 4: %x, 5: %x", 
        (unsigned int)SETUP.code[0], (unsigned int)SETUP.code[1], 
        (unsigned int)SETUP.code[2], (unsigned int)SETUP.code[3], 
        (unsigned int)SETUP.code[4]);
    printf("arr 0: %x, 1: %x, 2: %x, 3: %x, 4: %x, 5: %x", 
        (unsigned int)arr[0], 
        (unsigned int)arr[1], (unsigned int)arr[2], 
        (unsigned int)arr[3], (unsigned int)arr[4]);
    */
    sender_send_code(setup, SETUP.size);
    unsigned char play[5] = {0x7e, 0x03, 0x01, 0x02, 0xef};
    //sender_send_code(play, PLAY.size);
    unsigned char stop[5] = {0x7e, 0x03, 0x0e, 0x0d, 0xef};
    //sender_send_code(stop, STOP.size);    
}
    
