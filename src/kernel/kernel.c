#include "types.h"
#include "colors.h"

static int8_t *vidptr = (int8_t*)0xb8000;      // video begins here	

void kmain(void){
const char *boot_str = " _               _       ___  ____  \n"
                       "| |__   __ _ ___(_) ___ / _ \\/ ___| \n"
                       "| '_ \\ / _` / __| |/ __| | | \\___ \\ \n"
                       "| |_) | (_| \\__ \\ | (__| |_| |___) |\n"
                       "|_.__/ \\__,_|___/_|\\___|\\___/|____/ \n";
  uint32_t i = 0;
  uint32_t j = 0;

  // Cleaning the screen   
  while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
    vidptr[j] = ' ';                  // blank character
    vidptr[j+1] = LIGHT_GREY;
    j = j + 2;

  }
  
  j = 0;
  
  uint32_t current_row = 0;
  while(boot_str[j] != '\0'){
    vidptr[i] = boot_str[j];
	if (vidptr[i] == '\n'){
		i = (current_row + 1) * 80 * 2;
		j++;
		continue;
	}
    vidptr[i+1] = LIGHT_GREY;
    ++j;
    i = i + 2;

	current_row = i / (80 * 2);
  
  }
  
  return;

}
