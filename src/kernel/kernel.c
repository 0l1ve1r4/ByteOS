#include "types.h"
#include "colors.h"
#include "kernel.h"
#include "keyboard.h"

static int8_t *vidptr = (int8_t*) VIDEO_ADDRESS;    // video memory begins here
uint32_t current_loc = 0;                           // current location on the screen

void kmain(void){
    const char *boot_str = " _Welcome to the _       ___  ____  \n"
                        "| |__   __ _ ___(_) ___ / _ \\/ ___| \n"
                        "| '_ \\ / _` / __| |/ __| | | \\___ \\ \n"
                        "| |_) | (_| \\__ \\ | (__| |_| |___) |\n"
                        "|_.__/ \\__,_|___/_|\\___|\\___/|____/ \n"
                        "A simple x86 kernel written from scratch!\n\n";
    kclear();
    kprint(boot_str);
 
    kprint("root@kernel:~# ");
    idt_init();
    kb_init();
    
    while (1);
}


void keyboard_handler_main(void) {
	uint8_t status;
	char keycode;

	write_port(0x20, 0x20); // Write EOI

	status = read_port(KEYBOARD_STATUS_PORT);
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		if(keycode == ENTER_KEY_CODE) {
			kprint_nl();
			return;
		}

		vidptr[current_loc++] = keyboard_map[(unsigned char) keycode];
		vidptr[current_loc++] = 0x07;
	}
}



void kclear(void){
  uint32_t j = 0;
  while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
    vidptr[j] = ' ';                  // blank character
    vidptr[j+1] = LIGHT_GREY;
    j = j + 2;
  }
  return;
}

void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
        if (str[i] == '\n') {
            kprint_nl();
            i++;
            continue;
        }
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void kprint_nl(void) {
	uint32_t line_size = BYTES_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}