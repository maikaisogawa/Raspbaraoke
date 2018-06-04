#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "interrupts.h"
#include "printf.h"
#include "assert.h"

#define MP3_TX GPIO_PIN23;
#define MP3_RX GPIO_PIN24;
#define SONG1 GPIO_PIN5;
#define SONG2 GPIO_PIN6;
#define SONG3 GPIO_PIN13;
#define SONG4 GPIO_PIN19;
#define SONG5 GPIO_PIN26;
#define SONG6 GPIO_PIN21;
#define BAUD_RATE 
#define SETUP_CODE 0x7E054100045EF
#define PLAY_CODE 0x7E030102EF
#define STOP_CODE 0x7E030E0DEF
#define NUM_SONGS 6

//unsigned int[NUM_SONGS] songs;
static int curr;

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

void send_to_UART(int code, int pin) {
    if ((code == STOP_CODE) || (code == PLAY_CODE)) {
        gpio_write(MP3_RX);
    }
}

void change_song(void) {     //interrupt handler
    send_to_UART(STOP_CODE, -1);
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

     bool ok = interrupts_attach_handler(change_song);
     assert(ok);
     interrupts_enable_source(INTERRUPTS_GPIO3);
     interrupts_global_enable();
}

void setup(int song) {
     int code = SETUP_CODE;
     code = (code | (song << 16));  // four hex-places- need to convert to bit
     send_to_UART(code, song);
}

void play(void) {
     send_to_UART(PLAY_CODE, song);
}

void main() {

    buttons_init();
    setup_interrupts();
    
    while(!curr) {}
    
    int prev = curr;

    while(1) {  
         if (prev != curr) {
             setup(curr);
             prev = curr;
         }
         play(curr);
         printf(“curr is: %d”, curr);
    }

}

