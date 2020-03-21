#include "bool.h"
#include "screen.h"
#include "stringConsts.h"
#include "pair2d.h"
#include "io.h"
#define FB_CURSE_COMMAND_PORT  0x3d4
#define FB_CURSE_DATA_PORT 0x3d5
#define FB_CURSE_HIGH_COMMAND 14
#define FB_CURSE_LOW_COMMAND 15

#define NULL_TERMIN '\0'


void fb_write_char_simp(unsigned int line_pos, char c)
{
	*((char*)FRAME_BUFFER_ADR + line_pos) = c;

}

void fb_write_string_wrap_auto(
		struct uc_pair2d pos, 
		const char *str, 
		const struct fb_color_code color_code
		)
{
	unsigned int str_index = 0;
	unsigned int current_vga_cell = FB_LINE_POS(pos.x, pos.y);
	char current_char = str[str_index];

	while(current_char != NULL_TERMIN)
	{
		fb_write_cell(
				current_vga_cell,
			   	current_char, 
				(FB_COLOR_CODE_TO_UCHAR(color_code.fg, color_code.bg))); 

		current_vga_cell += 2; //Vga character cells are two bytes in length
		++str_index;
		current_char = str[str_index];

		if (line_pos_exceeds_max(current_vga_cell))
		{
			fb_shift_up(1);
			current_vga_cell -= 2 * FB_MAX_COLS; // Multiply by two since cells take up two bytes
		}
	}
}

void fb_write_string_wrap_safe(
		struct uc_pair2d pos,
		const char *str,
	   	const struct fb_color_code color_code
		)
{
	unsigned int str_index = 0;
	unsigned int current_vga_cell = FB_LINE_POS(pos.x, pos.y);
	char current_char = str[str_index];
	while(current_char != NULL_TERMIN && ! line_pos_exceeds_max(current_vga_cell))
	{
		fb_write_cell(
				current_vga_cell,
			   	current_char,
			   	FB_COLOR_CODE_TO_UCHAR(color_code.fg, color_code.bg)
				);
		current_vga_cell += 2; //Vga character cells are two bytes in length
		++str_index;
		current_char = str[str_index];
	}
}

void fb_write_string_wrap_direct(
		struct uc_pair2d pos,
	   	const char *str,
	   	const struct fb_color_code color_code
		)
{
	unsigned int str_index = 0;
	unsigned int current_vga_cell = FB_LINE_POS(pos.x, pos.y);
	char current_char = str[str_index];
	while(current_char != NULL_TERMIN)
	{
		//fb_write_cell_abstract(pos, 'F', (struct fb_color_code){0, 15});
		
		fb_write_cell(
				current_vga_cell,
			   	current_char, 
				FB_COLOR_CODE_TO_UCHAR(color_code.fg, color_code.bg)
				);
		current_vga_cell += 2; //Vga character cells are two bytes in length
		++str_index;
		current_char = str[str_index];
	}
}

bool line_pos_exceeds_max(unsigned int line_pos)
{
	return (line_pos > FB_MAX_LINE_POS);
}

struct uc_pair2d fb_char_line_pos_to_pos(unsigned int line_pos)
{
	unsigned char x = (char) (((line_pos/2) % FB_MAX_COLS)) ;
	unsigned char y = (char) ( ( ((line_pos/2) / FB_MAX_COLS)));
	return (struct uc_pair2d){x,y};
}

void fb_write_string_direct(
		struct uc_pair2d pos,
	   	const char* str,
	   	const struct fb_color_code color_code
		)
{
	unsigned int i = 0;
	struct uc_pair2d current_pos = fb_char_line_pos_to_pos(FB_LINE_POS(pos.x, pos.y));
	while(str[i] != NULL_TERMIN)
	{
		fb_write_cell_abstract(current_pos, str[i], color_code);
		++current_pos.x;
		++i;
	}
}

void fb_write_string_direct_noNull(
		struct uc_pair2d pos,
	   	const char* string,
	   	unsigned int len,
	   	struct fb_color_code color_code
		)
{
	struct uc_pair2d position = pos;
	for(unsigned int i = 0;i < len;i++)
	{
		fb_write_cell_abstract(position, string[i], color_code);
		position.x++;
	}
}

void fb_write_cell(unsigned int line_pos, char c, unsigned char color_code)
{
	fb_write_char(line_pos, c);
	fb_write_color(line_pos, color_code);
}

void fb_write_color(unsigned int cell_line_pos, unsigned char color_code)
{
	FB_BYTE(cell_line_pos + 1) = color_code; //The color code resides in the second byte
}

fb_write_char(unsigned int cell_line_pos, char c)
{
	FB_BYTE(cell_line_pos) = c;
}

void fb_write_cell_abstract(
		struct uc_pair2d pos,
	   	char c,
	   	struct fb_color_code color_code
		)
{
	// Mask first four bits of fg and bg, move fg to first four bits of bg
	fb_write_cell(FB_LINE_POS(pos.x, pos.y), c, FB_COLOR_CODE_TO_UCHAR(color_code.fg, color_code.bg));
}

void fb_moveCursor(struct uc_pair2d pos)
{
	unsigned short line_pos = FB_CURSOR_LINE_POS(pos.x, pos.y);

	outb(FB_CURSE_COMMAND_PORT, FB_CURSE_HIGH_COMMAND);
	//Shift the get the highest 8 bits of lineb_pos and send it to FB
	outb(FB_CURSE_DATA_PORT, ((line_pos >> 8) & 0x0ff));
	outb(FB_CURSE_COMMAND_PORT, FB_CURSE_LOW_COMMAND);
	//Take lowest 8 bits of line_pos
	outb(FB_CURSE_DATA_PORT, line_pos & 0x0ff);
}

void fb_shift_up(unsigned int distance)
{
	//Repeat scrolling until
	for(unsigned int i = 0; i < distance; ++i)
	{
		
		//For each row except the last
		for(int y = 0; y < (FB_MAX_ROWS - 1); y++)
		{
			for(unsigned int x =0; x < FB_MAX_COLS; x++)
			{
				//Copy The corresponding character from the row below
				//struct uc_pair2d pos = {(unsigned char)x,(unsigned char)y};
				unsigned int line_pos_dest = FB_LINE_POS(x, y);
				unsigned int line_pos_source = FB_LINE_POS(x, (y + 1));
				FB_BYTE(line_pos_dest) = FB_BYTE(line_pos_source);
				FB_BYTE(line_pos_dest + 1) = FB_BYTE(line_pos_source + 1);
			}
		}
		fb_clear_line(24);
	}
}

void fb_clear_line(unsigned char line)
{
	for (unsigned int x = 0; x < FB_MAX_COLS; x++)
	{
		unsigned int line_pos  = FB_LINE_POS(x, line);
		FB_BYTE(line_pos) = ' ';	
	}
}
