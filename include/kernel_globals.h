#ifndef	HOLY_SHIT_THESE_ARE_GLOBAL_VARIABLES_USED_BY_THE_KERNEL_FUCK_OH_FUCK_THE_MAGICNESS_
#define	HOLY_SHIT_THESE_ARE_GLOBAL_VARIABLES_USED_BY_THE_KERNEL_FUCK_OH_FUCK_THE_MAGICNESS_
#define KERNEL_DYNAMIC_MEMORY_SIZE 2097152 //KiB
#define KERNEL_DYNAMIC_MEMORY_PAGES 524288 //4KiB pages
#include "terminal.h"
#include "keyboard.h"
#include "ring_buffer.h"
#define KERNEL_KEYBOARD_BUFFER_SIZE 256
#define FIRST_FRAME_OFFSET 0x1000
#define FIRST_FRAME_ADDRESS_UNALIGNED ((PHYSICAL_KERNEL_END_ADDRESS + FIRST_FRAME_OFFSET))
#define FIRST_FRAME_ADDRESS (void*) (FIRST_FRAME_ADDRESS_UNALIGNED - (FIRST_FRAME_ADDRESS_UNALIGNED % 0x1000))
void kernel_globals_init();
extern Terminal main_terminal;
extern uc_ring_buffer kernel_keyboard_buffer;
extern unsigned char kernel_keyboard_buffer_data[KERNEL_KEYBOARD_BUFFER_SIZE];
extern Keyboard kernel_keyboard;
extern unsigned long kernel_page_directory[1024];
//262144] is 1 GiB
//Frame map is 2 GiB large for 4 KiB large pages
extern unsigned char kernel_frame_map[KERNEL_DYNAMIC_MEMORY_PAGES];
extern unsigned int _physical_kernel_start;
extern unsigned int _virtual_kernel_start;
extern unsigned int _physical_kernel_end;
extern unsigned int _virtual_kernel_end;
#define PHYSICAL_KERNEL_START_ADDRESS ((unsigned long) (&_physical_kernel_start))
#define PHYSICAL_KERNEL_END_ADDRESS ((unsigned long) (&_physical_kernel_end))
#define VIRTUAL_KERNEL_START_ADDRESS ((unsigned long) (&_virtual_kernel_start))
#define VIRTUAL_KERNEL_END_ADDRESS ((unsigned long) (&_virtual_kernel_end))
#endif
