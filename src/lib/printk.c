/**
 * Kernel print functions.
 */

#include "printk.h"

#include "vsprintf.h"
#include "../display/video_fb.h"

/**
 * Temporary stand-in main printk.
 *
 * TODO: This should print via UART, console framebuffer, and to a ring for
 * consumption by Horizon
 */
void printk(char *fmt, ...)
{
	va_list list;
	char buf[512];
	va_start(list, fmt);
	vsnprintf(buf, sizeof(buf), fmt, list);
	video_puts(buf);
	va_end(list);
}

// from: https://gist.github.com/ccbrown/9722406; temporary
void print_hex(const void* data, int size) {
	char ascii[17];
	int i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printk("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printk(" ");
			if ((i+1) % 16 == 0) {
				printk("|  %s \n   ", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printk(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printk("   ");
				}
				printk("|  %s \n   ", ascii);
			}
		}
	}
}

