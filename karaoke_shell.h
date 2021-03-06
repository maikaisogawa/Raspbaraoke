//
//  karaoke_shell.h
//  Created by Maika Isogawa on 6/7/18.
//

#ifndef karaoke_shell_h
#define karaoke_shell_h

/*
 * Interface to the CS107E shell - extended for final project.
 * This .h file may not include some functions that are already in the original shell.h file
 *
 * Author: Maika Isogawa
 *          Callan Hoskins
 *          Genevieve Singer
 * Date: June 2018
 */

typedef int (*formatted_fn_t)(const char *format, ...);

/*
 * shell_init
 * ==========
 *
 * Initialize the shell
 *
 * Takes a *function pointer* `printf_fn` that is used
 * to configure where the shell directs its output.
 *
 * Arguments:
 *   * `printf_fn` - used for the formatted output
 *
 * Example usage:
 *   * `shell_init(printf)`
 *   * `shell_init(console_printf)`
 */
void shell_init(formatted_fn_t print_fn);

/*
 * shell_readline
 * ==============
 *
 * Reads a single line of input from the user. Store the characters typed on
 * the keyboard and stores them into a buffer `buf` of size `bufsize`. Reading
 * stops when the user types enter (\n).
 *
 * When the user types backspace (\b):
 *   If there are any characters currently in the buffer, deletes the last one.
 *   Otherwise, calls `shell_bell`.
 */
void shell_readline(char buf[], int bufsize);

/*
 * shell_evaluate
 * ==============
 *
 * Parses a line as follows:
 *   * If the line is empty, does nothing
 *   * Otherwise, tokenizes the line. A token is a sequence of non-space
 *     characters.
 *   * Looks up the command function associated with the command name (first token).
 *   * If the command does not exist, prints an error such as:
 *       error: no such command 'binky'.
 *   * Otherwise, executes the command function with the rest of the tokens,
 *     using the rest of the tokens as arguments
 */
int shell_evaluate(const char *line);

/*
 * cmd_list
 * ==============
 *
 * Lists all available karaoke songs:
 *   * Song title - Song artist
 *   returns 0 upon successful completion
 */
int cmd_list(int argc, const char *argv[]);

/*
 * cmd_play
 * ==============
 *
 * Plays the selected karaoke song
 */
int cmd_play(int argc, const char *argv[]);

/*
 * function: capture_title
 * Takes the multiple arguments from shell input and creates a string that contains
 * the whole name of the song title. Returns a pointer to the title
 */
char * capture_title(int argc, const char *argv[]);



/*
 * shell_run
 * =========
 *
 * Main function of the shell module, must be called after `shell_init`.
 * Enters a read, eval, print loop that uses the  `shell_readline`, and
 * `shell_evaluate`, `printf_fn` (argument to `shell_init`).
 */
void karaoke_shell_run(void);

#endif /* karaoke_shell_h */
