#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "interrupts.h"
#include "printf.h"
#include "assert.h"

static const int MP3_TX = GPIO_PIN23;
static const int MP3_RX = GPIO_PIN24;
static const int SONG1 = GPIO_PIN5;
static const int SONG2 = GPIO_PIN6;
static const int SONG3 = GPIO_PIN13;
static const int SONG4 = GPIO_PIN19;
static const int SONG5 = GPIO_PIN26;
static const int SONG6 = GPIO_PIN21;
//#define SETUP_CODE (long)0x7E0541000045EF
//#define PLAY_CODE (long)0x7E030102EF
//#define STOP_CODE (long)0x7E030E0DEF
static int SETUP_CODE[7] = {0x7E, 0x05, 0x41, 0x00, 0x00, 0x45, 0xEF};
static int PLAY_CODE[7] = {0x7E, 0x03, 0x01, 0x02, 0xEF, 0xFF, 0xFF};
static int STOP_CODE[7] = {0x7E, 0x03, 0x0E, 0x0D, 0xEF, 0xFF, 0xFF};
#define NUM_SONGS 6

//unsigned int[NUM_SONGS] songs;
static int curr = -1;

void buttons_init(void) {
    gpio_set_input(SONG1);
    gpio_set_input(SONG2);
    gpio_set_input(SONG3);
    gpio_set_input(SONG4);
    gpio_set_input(SONG5);
    gpio_set_input(SONG6);
    gpio_set_pullup(SONG1);
    gpio_set_pullup(SONG2);
    gpio_set_pullup(SONG3);
    gpio_set_pullup(SONG4);
    gpio_set_pullup(SONG5);
    gpio_set_pullup(SONG6);
}

void send_to_UART(int code[7], int pin) {
    for(int i = 0; i < 7; i++) {
        printf("code byte: %x\n", code[i]);
    }
//    printf("initial 4 chars: %x", (code >> 16));
//    printf("you sent this code: %x to this pin %d\n", code, pin);
}

void change_song(void) {     //interrupt handler
    send_to_UART(STOP_CODE, curr);
    bool success = gpio_check_and_clear_event(SONG1);
    if (success) {
        curr = 1;
    }
 
    success = gpio_check_and_clear_event(SONG2);
    if (success) {
        curr = 2;
    }  

    success = gpio_check_and_clear_event(SONG3);
    if (success) {
        curr = 3;
    }  

    success = gpio_check_and_clear_event(SONG4);
    if (success) {
        curr = 4;
    }  

    success = gpio_check_and_clear_event(SONG5);
    if (success) {
        curr = 5;
    }

    success = gpio_check_and_clear_event(SONG6);
    if (success) {
        curr = 6;
    }
}

static void setup_interrupts(void) {
     gpio_enable_event_detection(SONG1, GPIO_DETECT_FALLING_EDGE);
     gpio_enable_event_detection(SONG2, GPIO_DETECT_FALLING_EDGE);
     gpio_enable_event_detection(SONG3, GPIO_DETECT_FALLING_EDGE);
     gpio_enable_event_detection(SONG4, GPIO_DETECT_FALLING_EDGE);
     gpio_enable_event_detection(SONG5, GPIO_DETECT_FALLING_EDGE);
     gpio_enable_event_detection(SONG6, GPIO_DETECT_FALLING_EDGE);

     bool ok = interrupts_attach_handler((void *)change_song);
     assert(ok);
     interrupts_enable_source(INTERRUPTS_GPIO3);
     interrupts_global_enable();
}

void setup(int song) {
    int code[7];
    for(int i = 0; i < 7; i++) {
        code[i] = SETUP_CODE[i];
    }
//    int code[7] = SETUP_CODE;
    code[5] = code[5] | song;
    send_to_UART(code, song);
//     long code = SETUP_CODE;
//     code = (code | (song << 16));  // four hex-places- need to convert to bit
//     send_to_UART(code, song);
}

void play(void) {
     send_to_UART(PLAY_CODE, curr);
}

void main(void) {

    buttons_init();
    setup_interrupts();
    
    while(curr == -1) {}
    
    int prev = curr;

    while(1) {  
         if (prev != curr) {
             setup(curr);
             prev = curr;
         }
         play();
//         printf("curr is: %d", prev);
    }

}

