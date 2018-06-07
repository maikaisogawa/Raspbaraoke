#include "sender.h"
#include "gpio.h"
#include "printf.h"

void test_sender_send_receive() {
    sender_send_code(0xff);
    unsigned int RECEIVED_CODE = sender_read_code();
    printf("%d\n", RECEIVED_CODE);
}

void main(void) {
    sender_init(GPIO_PIN23, GPIO_PIN24, 9600);
    test_sender_send_receive();
}
