#include "terminal.h"
#include "interrupt.h"
#include "pic.h"
#include "bool.h"
#include "keyboard.h"
#include "kernel_globals.h"
#include "keyboard_validification.h"
#include "vga_cursor.h"
#include "keyboard_ascii_conversion.h"
#include "keyboard_scanset_1_const.h"
#include "ring_buffer.h"
#include "memory.h"
#include "paging.h"
#include "pair2d.h"
void kernel_main()
{

	uc_pair2d pos = {0,10};
	fb_move_cursor(pos);
	idt_init();
	kernel_globals_init();	
	keyboard_init();
	char fuck[] = "FUCK\nASDF\nFOIAJEFPAOIJSEFFPAIJSE\0";
	terminal_print_hex(&main_terminal, 0x12112344);
	//terminal_vga_print(&main_terminal, fuck);
	//load_page_directory(kernel_page_directory);
	//enable_paging();
	char testnew[] = "\nHELLO:";
	
	char print;
	bool caps = true;
	while(true)
	{
		if(!uc_ring_buffer_empty(&kernel_keyboard_buffer))

		{
			unsigned char scan_code = uc_ring_buffer_dequeue(&kernel_keyboard_buffer);
			if(scan_code == KBDSC1_LEFT_SHIFT_P || scan_code == KBDSC1_RIGHT_SHIFT_P)
			{
				kernel_keyboard.caps = true;

			}
			else if(scan_code == KBDSC1_LEFT_SHIFT_R || scan_code == KBDSC1_RIGHT_SHIFT_R)
			{
				kernel_keyboard.caps=false;
			}

			if(keyboard_scancode_1_is_ascii(scan_code))
			{
				print = keyboard_scancode_1_pressed_to_ascii(&kernel_keyboard, scan_code);

				terminal_vga_print(
						&main_terminal,
						&print	
						);
			}
		}
	}
	
	//terminal_new_line(&term);
	

}
