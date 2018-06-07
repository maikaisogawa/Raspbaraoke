#include "console.h"
#include "gl.h"
#include "keyboard.h"
#include "printf.h"
#include "malloc.h" 
#include <stdarg.h>

#define BACKGROUND_COLOR GL_BLACK
#define TEXT_COLOR GL_GREEN

static char* tb;
static int head, bottom, cursor_pos_y, cursor_pos_x;
int rows, cols;

void console_init(unsigned int nrows, unsigned int ncols)
{
    gl_init(ncols*gl_get_char_width(), nrows*gl_get_char_height(),
        GL_DOUBLEBUFFER);
    tb = (char*)malloc(nrows*(ncols+1)); //+1 for '\0' null character
    rows = nrows;
    cols = ncols;
    console_clear();
}

/*
 * function: console_reset_line
 * Fills the given line with null ('\0') characters
 */
void console_reset_line(char* line) {
    for (int i = 0; i < cols + 1; i++) {
        line[i] = '\0'; //fill with null-terminators
    }
}

void console_clear(void)
{
    gl_clear(BACKGROUND_COLOR);
    //move cursor to (0,0)
    cursor_pos_y = 0;
    cursor_pos_x = 0;
    //erase the tb
    head = 0;
    bottom = 0;
    for (int y = 0; y < rows; y++) {
        console_reset_line(tb + y*(cols + 1));
    }
    gl_swap_buffer();
}

/* 
 * function: test_print_tb
 * Uses printf to print the contents of tb
 */
void test_print_tb(void) {
    for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < cols; j++) {
            char ch = *(tb + i*(cols + 1) + j);
            if (ch == '\0') ch = 'X';
            printf("%c", ch);
        }
        printf("row: %d", i);
        printf("\n");
    }
}

/*
 * function: console_backspace
 * Handle '\b' character passed to console_printf by writing over current char
 * with a '\0' and moving the cursor one position backwards.
 */
void console_backspace(void) {
    //handle case where cursor is on farthest left possible
    if (cursor_pos_x == 0) {
        if (cursor_pos_y == 0) return;
        *(tb + head*(cols + 1) + cursor_pos_x) = '\0';
        cursor_pos_y--;
        cursor_pos_x = cols - 1;
        head--;
    } else {
        *(tb + head*(cols + 1) + cursor_pos_x) = '\0';
        cursor_pos_x--;
        *(tb + head*(cols + 1) + cursor_pos_x) = '\0';
    }
}

void console_print_tb_to_fb(void) {
    gl_clear(BACKGROUND_COLOR);
    for (int y = 0; y < rows; y++) {
        int ypos = y + bottom;
        if (ypos >= rows) ypos = y + bottom - rows;
        gl_draw_string(0, y*gl_get_char_height(), tb + ypos*(cols + 1),
             TEXT_COLOR);
    }
    //draw cursor
    gl_draw_char(cursor_pos_x*gl_get_char_width(), 
        cursor_pos_y*gl_get_char_height(), '_', TEXT_COLOR);
}

/*
 * function: console_add_str_to_tb
 * Incorporates buf into tb at the current cursor position
 * @param buf - string of chars (not necessarily null-terminated) of size
 *      bufsize that should be added to the text buffer
 * 
 */
void console_add_str_to_tb(char* buf, int bufsize) {
    for (int i = 0; i < bufsize; i++) { 
        char ch = *(buf + i);
        //move to next line if overflowing current line
        if (cursor_pos_x >= cols) {
            *(tb + head*(cols+1) + cursor_pos_x) = '\0'; //null-terminator
            head++;
            if (head == rows) head = 0;
            console_reset_line(tb + head*(cols + 1));
            cursor_pos_x = 0;
            if (cursor_pos_y < (rows - 1)) cursor_pos_y++;
            else {
                bottom++;
            }
        }
        if (ch == '\n') { //handle newline
            cursor_pos_x = 0;
            if (cursor_pos_y < (rows - 1)) cursor_pos_y++;
            else bottom++;
            head++;
            if (head == rows) {
                head = 0;
            }
            console_reset_line(tb + head*(cols + 1));
        } else if (ch == '\f') { //handle clear
            console_clear();
        } else if (ch == '\b') { //handle backspace
            console_backspace();
        } else { //handle addition of regular char to tb
            *(tb + head*(cols + 1) + cursor_pos_x) = ch;
            cursor_pos_x++;
        }
        //check to see if head or bottom should be reset back to 0
        if (head == rows) head = 0; 
        if (bottom == rows) bottom = 0;
    }
}   

/*
 * function: min
 * Returns the smaller of two numbers
 */
int min(int a, int b) {
    if (a > b) return b;
    return a;
}

int console_printf(const char *format, ...)
{
    char buf[1024];
    int bufsize = 1024;
    va_list ap;
    va_start(ap, format);
    int res = vsnprintf(buf, bufsize, format, ap);
    buf[res] = '\0';
    console_add_str_to_tb(buf, min(res, bufsize)); //update text buffer
    console_print_tb_to_fb(); //display generated image
    gl_swap_buffer();
    va_end(ap);
    return res;
}
