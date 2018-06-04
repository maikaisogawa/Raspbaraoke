#include "gpio.h"
#include "gpioextra.h"
#include "keyboard.h"
#include "ps2.h"
#include "printf.h"
#include "interrupts.h"
#include "assert.h"
#include "ringbuffer.h"

/*
 * file: keyboard.c
 * Author: Callan Hoskins
 * Implements a simple user interface for PS/2 keyboard
 */

const unsigned int CLK  = GPIO_PIN23;
//const unsigned int DATA = GPIO_PIN24; 
unsigned int modifiers = 0;
static int keyboard_interrupts;
rb_t* rb;

void updateModifiers(keyboard_action_t action, unsigned char ch);
void turnOffSingleModifier(keyboard_modifiers_t to_be_off);
void turnOnsingleModifier(keyboard_modifiers_t to_be_on);
void flipSingleModifier(keyboard_modifiers_t to_be_flipped);

void keyboard_print_interrupts(void) {
    printf("Keyboard_interrupts: %d\n", keyboard_interrupts);
}

static void keyboard_entry(unsigned int pc) {
    static int total = 0;
    static int numOnes = 0;
    static int i = 0;
    if (gpio_check_event(CLK)) {
        gpio_clear_event(CLK);
        if (i > 0 && i < 9) { //read and add data bit
            int addition = gpio_read(DATA);
            numOnes += addition;
            addition = addition << (i - 1);
            total += addition;
            i++;
        } else if (i == 9) { //check parity bit
            unsigned char parityBit = gpio_read(DATA);
            numOnes += parityBit;
            i++;
        } else if (i == 10) {
            if (numOnes%2 == 1) {
               //add total to ringbuffer rb
               rb_enqueue(rb, total);
            } //reset scancode tracking
            numOnes = 0;
            total = 0;
            i = 0;
        } else { //i == 0
            i++;
        }
        keyboard_interrupts++;
    }
}

static void setup_interrupts(void) {
    gpio_enable_event_detection(CLK, GPIO_DETECT_FALLING_EDGE);
    bool ok = interrupts_attach_handler(keyboard_entry);
    if (!ok) {
        pi_abort();
    }
    interrupts_enable_source(INTERRUPTS_GPIO3);
    interrupts_global_enable();
    keyboard_interrupts = 0;
}

void wait_for_falling_clock_edge() {
    while (gpio_read(CLK) == 0) {}
    while (gpio_read(CLK) == 1) {}
}

void keyboard_init(void) 
{
    gpio_set_input(CLK); 
    gpio_set_pullup(CLK); 
 
    gpio_set_input(DATA); 
    gpio_set_pullup(DATA); 

    setup_interrupts();

    rb = rb_new();
}

unsigned char keyboard_read_scancode(void) 
{
    int scancode = 0;
    while (!rb_dequeue(rb, &scancode)) {}
    return (unsigned char)scancode;
/*
    unsigned char total_c;
    unsigned int numOnes;
    while (1) {
        total_c = 0;
        numOnes = 0;
        wait_for_falling_clock_edge();
        for (int i = 0; i < 8; i++) {
            wait_for_falling_clock_edge();
            unsigned char addition = gpio_read(DATA);
            numOnes += addition;
            addition = addition << i;
            total_c += addition;
        }
        wait_for_falling_clock_edge();
        unsigned int parityBit = gpio_read(DATA);
        numOnes += parityBit;
        wait_for_falling_clock_edge();
        if (numOnes%2 == 1) break;
    }
    return total_c;
*/
}

int keyboard_read_sequence(unsigned char seq[])
{
    int count = 0;
    seq[count] = keyboard_read_scancode();
    while (seq[count] == 0xe0 || seq[count] == 0xf0) {
        if (count > 2) return 3;
        count++;
        seq[count] = keyboard_read_scancode();
    }
    return count + 1;
}
/*
 * function: turnOffSingleModifier
 * Alters 'modifiers' to change the bit corresponding to to_be_off
 * to 0 (indicating that that modifier is off). 
 * @param to_be_off - number corresponding to key pressed/released
 */
void turnOffSingleModifier(keyboard_modifiers_t to_be_off) {
    modifiers = modifiers & (~to_be_off);
}

/*
 * function: turnOnSingleModifier
 * Alters 'modifiers' to change the bit corresponding to to_be_off
 * to 1 (indicating that the modifier is on). 
 * @param to_be_off - number corresponding to key pressed/released
 */
void turnOnSingleModifier(keyboard_modifiers_t to_be_on) {
    turnOffSingleModifier(to_be_on);
    modifiers = modifiers | to_be_on;
}

/*
 * function: flipSingleModifier
 * Flips the bit in 'modifiers' corresponding to to_be_flipped
 * from 0 to 1 or 1 to 0. 
 * @param to_be_flipped - number corresponding to key pressed/released
 */
void flipSingleModifier(keyboard_modifiers_t to_be_flipped) {
    int mod_prev_ON = modifiers & to_be_flipped;
    turnOffSingleModifier(to_be_flipped);
    if (!mod_prev_ON) {
        turnOnSingleModifier(to_be_flipped);
    }
}

/*
 * function: updateModifiers
 * Updates global variable 'modifiers' based on key event
 * If key event was SHIFT, CTRL, or ALT, makes changes to 'modifiers'
 * based on whether it was a key-up or key-down event. 
 * If key event was CAPS LOCK, NUM LOCK, or SCROLL LOCK, flips the
 * corresponding bit in 'modifiers'
 */   
void updateModifiers(keyboard_action_t action, unsigned char ch) {
    if (action == KEYBOARD_ACTION_DOWN) {
        if (ch == PS2_KEY_SHIFT) {
            turnOnSingleModifier(KEYBOARD_MOD_SHIFT);
        } else if (ch == PS2_KEY_ALT) {
            turnOnSingleModifier(KEYBOARD_MOD_ALT);
        } else if (ch == PS2_KEY_CTRL) {
            turnOnSingleModifier(KEYBOARD_MOD_CTRL);
        } else if (ch == PS2_KEY_CAPS_LOCK) {
            flipSingleModifier(KEYBOARD_MOD_CAPS_LOCK);
        } else if (ch == PS2_KEY_NUM_LOCK) {
            flipSingleModifier(KEYBOARD_MOD_NUM_LOCK);
        } else if (ch == PS2_KEY_SCROLL_LOCK) {
            flipSingleModifier(KEYBOARD_MOD_SCROLL_LOCK);
        }
    } else {//action up
        if (ch == PS2_KEY_SHIFT) {
            turnOffSingleModifier(KEYBOARD_MOD_SHIFT);
        } else if (ch == PS2_KEY_ALT) {
            turnOffSingleModifier(KEYBOARD_MOD_ALT);
        } else if (ch == PS2_KEY_CTRL) {
            turnOffSingleModifier(KEYBOARD_MOD_CTRL);
        }
    }
}

key_event_t keyboard_read_event(void) 
{
    key_event_t event;
    event.seq_len = keyboard_read_sequence(event.seq);
    int head = 0;
    if (event.seq[head] == PS2_CODE_RELEASE) {
        event.action =  KEYBOARD_ACTION_UP;
        head++;
    } else {
        event.action = KEYBOARD_ACTION_DOWN;    
    }
    if (event.seq[head] == PS2_CODE_EXTEND) head++;
    event.key = ps2_keys[event.seq[head]];
    updateModifiers(event.action, event.key.ch);
    event.modifiers = modifiers;
    return event;
}

unsigned char keyboard_read_next(void) 
{
    while (true) {
        key_event_t event = keyboard_read_event();
        if (event.action == KEYBOARD_ACTION_UP) continue;
        if (event.key.ch == PS2_KEY_ALT ||
            event.key.ch == PS2_KEY_CTRL ||
            event.key.ch == PS2_KEY_SHIFT || 
            event.key.ch == PS2_KEY_CAPS_LOCK ||
            event.key.ch == PS2_KEY_NUM_LOCK ||
            event.key.ch == PS2_KEY_SCROLL_LOCK) continue;
        int CAPS_LOCK_STATUS = modifiers & KEYBOARD_MOD_CAPS_LOCK;
        int SHIFT_STATUS = modifiers & KEYBOARD_MOD_SHIFT;
        if ((CAPS_LOCK_STATUS || SHIFT_STATUS) && 
            (event.key.ch >= 'a' && event.key.ch <= 'z')) {
            return event.key.other_ch;
        }
        if (event.key.ch < 0x7f) {
            if (SHIFT_STATUS) {
                return event.key.other_ch;
            }
        }
        return event.key.ch;
    }
}
