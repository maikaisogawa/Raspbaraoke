#include "songs.h"
#include "printf.h"
#include "console.h"
#include "gpio.h"
#include "karaoke_shell.h"
#include "shell.h"
#include "gl.h"
#include "keyboard.h"
#include "printf.h"
#include "malloc.h"
#include <stdarg.h>

void main() 
{
//    gpio_init();
//    console_init(20, 40);
//    keyboard_init();
    
//    shell_init(console_printf);
//    karaoke_shell_run();
    songs_init();

}
