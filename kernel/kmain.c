#include "screen.h"
#include "bool.h"
void kmain()
{
	//const int frame_adr = 0x000b8000;
	//char *frame_buffer = (char*)frame_adr;
	struct fb_color_code wb = {0, 12};

	char fuck_more[] = {"FFUFF$FFCK OH FFUCK OH FFUCK OH FFUCK OHFUCK OH FUCK OH FUCK\0"};
	char test_num[] = {"1234567890987654321\0"};
	fb_moveCursor( (struct uc_pair2d){0,0});
	struct uc_pair2d pos = {0,24};
	struct uc_pair2d po2 = {40,0};

	fb_write_char_abstract((struct uc_pair2d){0,0}, 'A', wb);
	fb_write_char_abstract((struct uc_pair2d){79,24}, 'B', wb);
	fb_write_char_abstract((struct uc_pair2d){0,24}, 'C', wb);
	fb_write_char_abstract((struct uc_pair2d){79,0}, 'C', wb);

	//char fuck_longer[] = {"THIS IS A LOT OF FUCKING TEST MASTERS GIVE ME MORE YES PLEASE AHHHH YES I LIKE IT I WANT MORE MAGIC NUMBERS SHOVE THEM UP MY USB PORT AND THROUGH MY SKULL \0"};
	fb_write_string_wrap(po2, fuck_more, wb);

	//fb_shift_up(1);
	//bool right = true;
	//int move_length = 50;
	//int x_val = 0;
	//int wait = 1;
	//int wait_time = 1;
	fb_write_string_direct(pos, fuck_more, wb);
	/*
	while(true)
	{
		if(wait == 0)
		{
			fb_write_string_direct(pos, fuck, wb);

			if(right)
			{
				x_val++;
				if(x_val >= move_length)
				{
					right = false;
				}
			}
			else
			{
				x_val--;
				if(x_val <= 0)
				{
					right = true;
				}
			}

			pos.x = x_val;
			fb_shift_up(1);
			wait = wait_time;
		}
		else
		{
			wait--;
		}
	}
	//for(int i = 0 ; i < 10; ++i)
	//{
	//	fb_shift_up(1);
	//	fb_write_char(pos, 'Z', wb);
	//	fb_write_char(pos2, 'X', wb);
	//}
	*/
}