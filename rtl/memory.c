#include "memory.h"
#include "paging.h"
#include "math.h"

pageframe_t memalloc(unsigned long amount_of_bytes)
{
	double frames_needed = CEILING((double)amount_of_bytes /0x1000);
	return kcontinuous_alloc(frames_needed);
}