#include "shell.h"
#include "shell_commands.h"
#include "uart.h"
#include "keyboard.h"
#include "strings.h"
#include "malloc.h"
#include "pi.h"
#include "gl.h"
#include "songs.h"
#include "timer.h"
#include "console.h"
#include "mp3.h"

/*
 * karaoke_shell.c
 * Author: Callan A. Hoskins, Maika Isogawa, Genevieve Singer
 * 6 June 2018
 * This file extends a basic shell program, using an attached PS/2 key-
 * board. Call functions like 'help', 'echo', and 'list'
*/

#define LINE_LEN 80
#define BACKSPACE 0x8
#define SPACE ' '

// prototypes of commands added for karaoke shell, shell extension
int cmd_list(int argc, const char *argv[]);
int cmd_play(int argc, const char *argv[]);

static int (*shell_printf)(const char * format, ...); 
static const command_t commands[] = {
    {"help",   "<cmd> prints a list of commands or description of cmd", cmd_help},
    {"echo",   "<...> echos the user input to the screen", cmd_echo},
    {"reboot", "reboots the Pi back to the bootloader", cmd_reboot},
    {"list", "lists the songs available for play", cmd_list},
    {"play", "plays the selected song", cmd_play},
};

int cmd_list(int argc, const char *argv[]) {
    song_t * library = load_songs();
 //   shell_printf("    + %s - %s\n", songs_get_title(library[0]));
    for(int i = 0; i < NUM_SONGS; i++) {
        shell_printf("    + %s - %s\n", songs_get_title(library[i]), songs_get_artist(library[i]));
    }
    return 0;
}

int cmd_play(int argc, const char *argv[]) {
    song_t * library = load_songs();
    for(int i = 0; i < NUM_SONGS; i++) {
        if(strcmp(argv[1], songs_get_title(library[i])) == 0) {
            mp3_play_song(5); // change this to play the approprate song [i]
        }
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

void karaoke_intro(void) {
    shell_printf("\n\n\n\n\n\n\n\n\n        Welcome to Raspbaraoke!\n");
    timer_delay(3);
    // bunch of graphical stuff here
    gl_draw_rect(0, 0, gl_get_width() / 10, gl_get_width() / 10, GL_AMBER);
    gl_swap_buffer();
    timer_delay(3);
    console_init(20, 40);
    shell_printf("         Please select a song! \n\n Type 'play' followed by the song title\n");
}

void karaoke_shell_run(void)
{
    karaoke_intro();
  //  shell_printf("Welcome to the Karaoke shell!\n");
    while (1) 
    {
        char line[LINE_LEN + 1]; //effective line length = 80 (+'\0')
        shell_printf("Pi> ");
        shell_readline(line, sizeof(line));
        shell_evaluate(line);
    }
}
