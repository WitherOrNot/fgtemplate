#include "utils.h"
#include "hwinit.h"
#include "lib/printk.h"
#include "display/video_fb.h"

#include "fuse.h"
#include "hwinit/btn.h"
#include "hwinit/util.h"

#define XVERSION 1

static void reset_using_pmc()
{
	volatile uint32_t *reset;

	reset = (uint32_t *)0x7000e400;
	*reset |= (1 << 4);
}

int main(void) {
	u32 *lfb_base;
	
	nx_hwinit();
	display_init();
	
	// Set up the display, and register it as a printk provider.
	lfb_base = display_init_framebuffer();
	video_init(lfb_base);
	
	printk("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printk("Compiled the template without changing the code huh ;)\n");
	printk("Well, congratulations. Your reward is a button test.\n");
	printk("Fusee Template by @witherornot1, fusee gelee by @ktemkin\n");
	
	// Wait for the power button, and then reset.
	while (1) {
		int pressed = btn_read();
		
		if (pressed == BTN_POWER) {
			printk("Power button press detected\n");
		} else if (pressed == BTN_VOL_UP) {
			printk("Volume up button press detected\n");
		} else if (pressed == BTN_VOL_DOWN) {
			printk("Volume down button press detected\n");
		}
	}
	
	reset_using_pmc();
	
	/* Do nothing for now */
	return 0;
}