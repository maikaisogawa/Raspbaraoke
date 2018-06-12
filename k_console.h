#ifndef CONSOLE_H
#define CONSOLE_H

/*
 * Interface to an ADVANCED text console displayed on the screen.
 *
 * Author: Callan Hoskins
 * Date: 3/24/18
 */


/*
 * Initialize the console. The console text begins empty and
 * the cursor is in the home position (upper left corner).
 *
 * @param nrows the requested number of rows in characters
 * @param ncols the requested number of columns in characters
 */
void console_init(unsigned int nrows, unsigned int ncols);

/*
 * Clear all console text and move the cursor to the home
 * position.
 */
void console_clear(void);

/*
 * Print the formatted string to the console starting at current cursor
 * position. The arguments to this function are the same as `printf`.
 * When processing characters, interpret the following special characters:
 *
 * '\n' :  newline (move cursor down to the beginning of next line)
 * '\b' :  backspace (move cursor backwards one position)
 * '\f' :  form feed (clear contents and move cursor to home position)
 *
 * @param (x,y) - x,y coordinates where text should be written
 * @return the number of characters written to the console
 */
int console_printf(unsigned int x, unsigned int y, const char *format, ...);

void draw_song_cover(int x, int y, int h, int w);

#endif
