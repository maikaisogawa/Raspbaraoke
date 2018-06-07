#include "shell.h"
#include "shell_commands.h"
#include "uart.h"
#include "keyboard.h"
#include "strings.h"
#include "malloc.h"
#include "pi.h"
#include "songs.h"

/*
 * karaoke_shell.c
 * Author: Callan A. Hoskins, Maika Isogawa, Gen
 * 6 June 2018
 * This file extends a basic shell program, using an attached PS/2 key-
 * board. Call functions like 'help', 'echo', and 'list'
*/

#define LINE_LEN 80
#define BACKSPACE 0x8
#define SPACE ' '

static int (*shell_printf)(const char * format, ...); 
static const command_t commands[] = {
    {"help",   "<cmd> prints a list of commands or description of cmd", cmd_help},
    {"echo",   "<...> echos the user input to the screen", cmd_echo},
    {"reboot", "reboots the Pi back to the bootloader", cmd_reboot},
    {"list", "lists the songs available for play", cmd_list},
    {"play", "plays the selected song", cmd_play},
 //   {"peek", "[address] prints the value stored at memory address 'address'", cmd_peek},
 //   {"poke", "[address][value] stores 'value' in the memory address 'address'", cmd_poke}
};

int cmd_list(void) {
    for(int i = 0; i < NUM_SONGS; i++) {
        // shell_printf("%s - %s\n", // song title, // song artist);
    }
    return 0;
}

int cmd_play(void) {
    for(int i = 0; i < NUM_SONGS; i++) {
        // loop through list of song titles
        // when find song title matches
        // shift instruction to include appropriate song
        // send instruction to play song
    }
    return 0;
}

/*
 * function: cmd_echo
 * Prints everything entered by the user after they type 'echo'
 */
int cmd_echo(int argc, const char *argv[]) 
{
    for (int i = 1; i < argc; ++i) 
        shell_printf("%s ", argv[i]);
    shell_printf("\n");
    return 0;
}

/*
 * function: cmd_help
 * Prints a list of commands or description of once specific command
 */
int cmd_help(int argc, const char *argv[]) 
{
    //user didn't specify command
    if (argc < 2) {
        for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
            shell_printf("%s: %s\n", commands[i].name, 
                commands[i].description);
        }
        return 0;
    }
    //user specified command, so search for that command
    for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
        if (strcmp(commands[i].name, argv[1]) == 0) {
            shell_printf("%s: %s\n", commands[i].name, 
                commands[i].description);
            return 0;
        }
    }
    //handle error
    shell_printf("error: no such command '%s'\n", argv[1]);
    return 1;
}

/*
 * function: cmd_reboot
 * Reboots the Pi
 */
int cmd_reboot(int argc, const char *argv[]) {
   pi_reboot(); 
   return 0;
}

/*
 * function: cmd_peek
 * Prints the value stored at the address specified in the 1st parameter
 * Throws error if given more than one argument, if the address
 * specified is not a valid number, or the address is not 4-byte-
 * aligned. 
 */
//int cmd_peek (int argc, const char* argv[]) {
//    if (argc < 2) {
//        shell_printf("error: peek expects 1 argument [address]\n");
//        return 1;
//    }
//    //int addr_len = strlen(argv[1]);
//    const char* addr_str = argv[1];
//    const char **endptr = &argv[1];
//    unsigned int* addr = (unsigned int*)strtonum(argv[1],
//        endptr);
//    if (**endptr != '\0') {
//        argv[1] = addr_str;
//        shell_printf("error: peek cannot convert '%s'\n", argv[1]);
//        return 1;
//    }
//    argv[1] = addr_str;
//    if (((unsigned int)addr)%4 != 0) {
//        shell_printf("error: peek address must be 4-byte aligned\n");
//        return 1;
//    }
//    unsigned int val = *addr;
//    shell_printf("0x%08x: %08x\n", (unsigned int)addr, val);
//    return 0;
//}

/*
 * function: cmd_poke
 * Writes value stored in the second argument to the memory address
 * provided in the first argument. 
 * Throws error if there are less than 3 arguments, the memory address
 * specified isn't 4-byte aligned, or either argument cannot be 
 * converted to an integer. 
 */
//int cmd_poke(int argc, const char* argv[]) {
//    if (argc < 3) {
//         shell_printf("error: poke expects 2 arguments [address][value]\n");
//         return 1;
//     }
//     const char* addr_str = argv[1];
//     const char **endptr = &argv[1];
//     unsigned int* addr = (unsigned int*)strtonum(argv[1],
//         endptr);
//     if (**endptr != '\0') {
//         argv[1] = addr_str;
//         shell_printf("error: poke cannot convert '%s'\n", argv[1]);
//         return 1;
//     }
//     if (((unsigned int)addr)%4 != 0) {
//        argv[1] = addr_str;
//        shell_printf("error: poke address must be 4-byte aligned\n");
//        return 1;
//     }
//     unsigned int val = (unsigned int)strtonum(argv[2], endptr);
//     if (**endptr != '\0') {
//        shell_printf("error: poke cannot convert '%s'\n", argv[2]);
//        argv[1] = addr_str;
//        return 1;
//     }
//     argv[1] = addr_str;
//     *addr = val;
//     return 0;
//}

void shell_init(formatted_fn_t print_fn)
{
    shell_printf = print_fn;
}

void shell_bell(void)
{
    uart_putchar('\a');
}

void shell_readline(char buf[], int bufsize)
{
    int index = 0;
    unsigned char ch = keyboard_read_next(); //use connected PS2 keyboard
    while (ch != '\n' && index < bufsize - 1) {
        //handle backspace
        if (ch == BACKSPACE) {
            if (index == 0) {
                shell_bell();
            } else {
                shell_printf("%c", BACKSPACE);
                index--;
            }
        } else {
            shell_printf("%c", ch);
            buf[index] = ch;
            index++;
        }
        ch = keyboard_read_next();
    }
    shell_printf("%c", '\n');
    buf[index] = '\0'; //null-terminator, turns line into string
}

/*
 * function: getNumSpaces
 * Returns the number of tokens in line
 */
int getNumTokens(const char *line) {
    int tokens = 0;
    int i = 0;
    //searches for the beginning of each token  within line
    while (i < strlen(line)) {
        if (line[i] == SPACE) {
            i++;
        } else {
            tokens++;
            while (line[i] != SPACE && i < strlen(line)) i++;
        }
    }
    return tokens;
}

/*
 * function: getParams
 * Reads line to find tokenize line and store tokens as char*
 * in params. 
 */
void getParams(char* params[], const char* line) {
    int i = 0;
    int token = 0;
    while (i < strlen(line)) {
        //skip over spaces
        if (line[i] == SPACE) {
            i++;
        } else { //found a token
            int sizeOfToken = 0;
            while (i < strlen(line) && line[i] != SPACE) {
                i++;
                sizeOfToken++;
            }
            //store token in params
            params[token] = (char*)malloc(sizeOfToken + 1);
            memcpy(params[token], line + i - sizeOfToken, sizeOfToken);
            *(params[token] + sizeOfToken) = '\0'; //null-terminator
            token++; //set up for next token
        }
    }
}

/* 
 * function: freeMemory
 * Calls free(...) from malloc.h on each char* in ch_arr to prevent 
 * memory leak. After function call, ch_arr will not be guaranteed to
 * contain its previous data. 
 */
void freeMemory(char* ch_arr[], int elems) {
    for (int i = 0; i < elems; i++) {
        free(ch_arr[i]);
    }
}

int shell_evaluate(const char *line)
{
    int tokens = getNumTokens(line);
    if (tokens == 0) return 0; //successful if line is empty
    char* params[tokens];
    getParams(params, line);
    struct _command_struct cmd;
    cmd.name = "unknown";
    //iterate over each command in commands to see if there's a match
    for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
        if (strcmp(params[0], commands[i].name) == 0) {
            cmd = commands[i];
            break;
        }
    }
    if (strcmp(cmd.name, "unknown") == 0) {
        shell_printf("error: no such command '%s'.\n", params[0]);
        return 1; //unsuccessful
    }
    int res =  (int)cmd.fn(tokens, (const char**)params);
    freeMemory(params, tokens);
    return res;
}

void shell_run(void)
{
    shell_printf("Welcome to the CS107E shell. Remember to type on your PS/2 keyboard!\n");
    while (1) 
    {
        char line[LINE_LEN + 1]; //effective line length = 80 (+'\0')

        shell_printf("Pi> ");
        shell_readline(line, sizeof(line));
        shell_evaluate(line);
    }
}
