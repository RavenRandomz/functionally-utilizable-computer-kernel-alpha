#ifndef FUCK_YEAH_TERMINAL_CODE_OR_AT_LEAST_DISPLAY
#define FUCK_YEAH_TERMINAL_CODE_OR_AT_LEAST_DISPLAY
#include "pair2d.h"
#include "vga_util.h"
#include "vga_const_color.h"
#include "vga_const.h"
typedef struct 
{

	uc_pair2d cursor_pos;
	uc_pair2d screen_size;
	fb_color_code default_color;

}Terminal;

#define TERMINAL_DEFAULT ((Terminal){{0, 0},{FB_MAX_COLS, FB_MAX_ROWS}, FB_MATRIX_COLORZ})


void terminal_vga_print(Terminal* terminal, const char* string);
#endif

